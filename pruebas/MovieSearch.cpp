#include "MovieSearch.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

MovieSearchEngine& MovieSearchEngine::getInstance() {
    static MovieSearchEngine instance;
    return instance;
}

void MovieSearchEngine::loadMovies(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return;}

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

void MovieSearchEngine::addStrategy(unique_ptr<SearchStrategy<Movie>> strategy) {
    strategies.push_back(move(strategy));
}

vector<Movie> MovieSearchEngine::search(const string& query) {
    vector<Movie> results;

    for (const auto& strategy : strategies) {
        auto strategyResults = strategy->search(movies, query);
        results.insert(results.end(), strategyResults.begin(), strategyResults.end());
    }

    // Eliminar duplicados (opcional)
    sort(results.begin(), results.end(), [](const Movie& a, const Movie& b) {
        return a.imdb_id < b.imdb_id;
    });
    results.erase(std::unique(results.begin(), results.end(), [](const Movie& a, const Movie& b) {
        return a.imdb_id == b.imdb_id;
    }), results.end());

    return results;
}

vector<Movie> TitleSearch::search(const vector<Movie>& movies, const string& query) {
    vector<Movie> results;
    for (const auto& movie : movies) {
        if (movie.title.find(query) != string::npos) {
            results.push_back(movie);
        }
    }
    return results;
}

vector<Movie> TagSearch::search(const vector<Movie>& movies, const string& query) {
    vector<Movie> results;
    for (const auto& movie : movies) {
        if (movie.tags.find(query) != string::npos) {
            results.push_back(movie);
        }
    }
    return results;
}

vector<Movie> PlotSearch::search(const vector<Movie>& movies, const string& query) {
    std::vector<Movie> results;
    for (const auto& movie : movies) {
        if (movie.plot_synopsis.find(query) != string::npos) {
            results.push_back(movie);
        }
    }
    return results;
}

int MovieSearchEngine::calculateRelevance(const Movie& movie, const string& query) {
    // Implement relevance calculation if needed
    return 0;
}
