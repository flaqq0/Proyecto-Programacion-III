#include "MovieSearch.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <future>

Buscador& Buscador::getInstance() {
    static Buscador instance;
    return instance;
}
void Buscador::loadMovies(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string imdb_id, title, plot_synopsis, tags, split, synopsis_source;

        getline(ss, imdb_id, ';');
        getline(ss, title, ';');
        getline(ss, plot_synopsis, ';');
        getline(ss, tags, ';');
        getline(ss, split, ';');
        getline(ss, synopsis_source, ';');

        Movie movie(imdb_id, title, plot_synopsis, tags, split, synopsis_source);
        movies.push_back(movie);

        cout << "Loaded movie: " << title << endl;
    }

    file.close();
}

void Buscador::loadCSV(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return;
    }

    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string c;
        Movie* movie;
        bool dentroQuotes = false;
        string field;
        int fieldIndex = 0;
        while (getline(ss, c, ',')) {
            if (c.front() == '"' && !dentroQuotes) {
                dentroQuotes = true;
                field += c.substr(1);
            } else if (c.back() == '"' && dentroQuotes) {
                dentroQuotes = false;
                field += ',' + c.substr(0, c.size() - 1);
                switch (fieldIndex) {
                    case 2: movie->plot_synopsis = field;
                        break;
                    case 3: movie->tags = field;
                        break;
                    default: break;
                }
                field.clear();
                fieldIndex++;
            } else if (dentroQuotes) {
                field += ',' + c;
            } else {
                switch (fieldIndex) {
                    case 0: movie->imdb_id = c;
                        break;
                    case 1: movie->title = c;
                        break;
                    case 4: movie->split = c;
                        break;
                    case 5: movie->synopsis_source = c;
                        break;
                    default: break;
                }
                fieldIndex++;
            }
        }
        if (!field.empty()) {
            if (fieldIndex == 2) movie->plot_synopsis = field;
            else if (fieldIndex == 3) movie->tags = field;
        }
        movies.push_back(*movie);
    }

    file.close();
}


void Buscador::addEstrategia(unique_ptr<Estrategia> strategy) {
    strategies.push_back(move(strategy));
}

vector<Movie> Buscador::buscar(const string& query) {
    vector<future<vector<Movie>>> futures;

    for (const auto& strategy : strategies) {
        futures.push_back(async(&Estrategia::search, strategy.get(), movies, query));
    }

    vector<Movie> results;
    for (auto& future : futures) {
        auto strategyResults = future.get();
        results.insert(results.end(), strategyResults.begin(), strategyResults.end());
    }

    sort(results.begin(), results.end(), [](const Movie& a, const Movie& b) {
        return a.imdb_id < b.imdb_id;
    });
    results.erase(unique(results.begin(), results.end(), [](const Movie& a, const Movie& b) {
        return a.imdb_id == b.imdb_id;
    }), results.end());

    vector<pair<int, Movie>> relevantResults;
    for (const auto& movie : results) {
        int relevance = calcularRelevancia(movie, query);
        relevantResults.emplace_back(relevance, movie);
    }

    sort(relevantResults.begin(), relevantResults.end(), [](const pair<int, Movie>& a, const pair<int, Movie>& b) {
        return a.first > b.first;
    });

    vector<Movie> sortedResults;
    for (const auto& pair : relevantResults) {
        sortedResults.push_back(pair.second);
    }

    return sortedResults;
}

int Buscador::calcularRelevancia(const Movie& movie, const string& query) {
    int relevance = 0;
    relevance += contador(movie.title, query) * 3;
    relevance += contador(movie.tags, query) * 2;
    relevance += contador(movie.plot_synopsis, query);
    return relevance;
}

int Buscador::contador(const string& text, const string& word) {
    int count = 0;
    size_t pos = text.find(word, 0);
    while (pos != string::npos) {
        ++count;
        pos = text.find(word, pos + word.length());
    }
    return count;
}

vector<Movie> PorTitulo::search(const vector<Movie>& movies, const string& query) {
    vector<Movie> results;
    for (const auto& movie : movies) {
        if (movie.title.find(query) != string::npos) {
            results.push_back(movie);
        }
    }
    return results;
}

vector<Movie> PorTag::search(const vector<Movie>& movies, const string& query) {
    vector<Movie> results;
    for (const auto& movie : movies) {
        if (movie.tags.find(query) != string::npos) {
            results.push_back(movie);
        }
    }
    return results;
}

vector<Movie> PorPlot::search(const vector<Movie>& movies, const string& query) {
    vector<Movie> results;
    for (const auto& movie : movies) {
        if (movie.plot_synopsis.find(query) != string::npos) {
            results.push_back(movie);
        }
    }
    return results;
}