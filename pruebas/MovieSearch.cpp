#include "MovieSearch.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <regex>
#include <future>

using namespace std;

Buscador& Buscador::getInstance() {
    static Buscador instance;
    return instance;
}

void Buscador::loadMovies(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        throw runtime_error("Error opening file: " + filePath);
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
        movieMap[imdb_id] = movie;
    }

    file.close();
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::vector<std::string> splitCSVLine(const std::string& line) {
    std::vector<std::string> result;
    std::stringstream ss(line);
    std::string field;
    bool in_quotes = false;
    char c;
    std::string current_field;

    while (ss.get(c)) {
        if (c == '"' && (current_field.empty() || current_field.back() != '\\')) {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            result.push_back(trim(current_field));
            current_field.clear();
        } else {
            current_field += c;
        }
    }
    result.push_back(trim(current_field));

    return result;
}

Movie parseLine(const std::string& line) {
    std::vector<std::string> fields = splitCSVLine(line);
    Movie movie;

    if (fields.size() >= 6) {
        movie.imdb_id = fields[0];
        movie.title = fields[1];
        movie.plot_synopsis = fields[2];
        movie.tags = fields[3];
        movie.split = fields[4];
        movie.synopsis_source = fields[5];
    }

    return movie;
}

std::vector<Movie> readCSV(const std::string& filename) {
    std::vector<Movie> movies;
    std::ifstream file(filename);
    std::string line;
    std::string combined_line;
    std::regex imdb_id_pattern(R"(^tt\d{7})");

    std::getline(file, line);

    while (std::getline(file, line)) {
        if (std::regex_search(line, imdb_id_pattern)) {
            if (!combined_line.empty()) {
                movies.push_back(parseLine(combined_line));
                combined_line.clear();
            }
        }

        if (!combined_line.empty()) {
            combined_line += "\n";
        }
        combined_line += line;
    }

    if (!combined_line.empty()) {
        movies.push_back(parseLine(combined_line));
    }

    file.close();
    return movies;
}

void Buscador::loadCSV(const string& filePath) {
    movies = readCSV(filePath);
    for (const auto& movie : movies) {
        movieMap[movie.imdb_id] = movie;
    }
}

void Buscador::addEstrategia(unique_ptr<Estrategia> strategy) {
    strategies.push_back(move(strategy));
}

vector<Movie> Buscador::buscar(const string& query) {
    vector<future<vector<Movie>>> futures;

    for (const auto& strategy : strategies) {
        futures.push_back(async(&Estrategia::search, strategy.get(), movies, query));
    }

    unordered_set<string> seen;
    vector<Movie> results;

    for (auto& future : futures) {
        auto strategyResults = future.get();
        for (const auto& movie : strategyResults) {
            if (seen.find(movie.imdb_id) == seen.end()) {
                seen.insert(movie.imdb_id);
                results.push_back(movie);
            }
        }
    }

    vector<pair<int, Movie>> relevantResults;
    for (const auto& movie : results) {
        int relevance = calcularRelevancia(movie, query);
        relevantResults.emplace_back(relevance, movie);
    }

    sort(relevantResults.begin(), relevantResults.end(), [](const pair<int, Movie>& a, const pair<int, Movie>& b) {
        return a.first > b.first;
    });

    vector<Movie> topResults;
    int count = 0;
    for (const auto& pair : relevantResults) {
        if (count >= 5) break;
        topResults.push_back(pair.second);
        ++count;
    }

    return topResults;
}

int Buscador::calcularRelevancia(const Movie& movie, const string& query) {
    int relevance = 0;
    relevance += contador(movie.title, query) * 3;
    relevance += contador(movie.tags, query) * 2;
    relevance += contador(movie.plot_synopsis, query);
    return relevance;
}

template<typename T>
int Buscador::contador(const T& text, const T& word) {
    int count = 0;
    size_t pos = text.find(word, 0);
    while (pos != T::npos) {
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
