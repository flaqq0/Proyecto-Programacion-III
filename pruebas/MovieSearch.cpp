#include "MovieSearch.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

MovieSearchEngine& MovieSearchEngine::getInstance() {
    static MovieSearchEngine instance;
    return instance;
}

void MovieSearchEngine::loadMovies(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string imdb_id, title, plot_synopsis, tags, split, synopsis_source;

        std::getline(ss, imdb_id, ';');
        std::getline(ss, title, ';');
        std::getline(ss, plot_synopsis, ';');
        std::getline(ss, tags, ';');
        std::getline(ss, split, ';');
        std::getline(ss, synopsis_source, ';');

        Movie movie(imdb_id, title, plot_synopsis, tags, split, synopsis_source);
        movies.push_back(movie);

        // Debug print to verify movie loading
        std::cout << "Loaded movie: " << title << std::endl;
    }

    file.close();
}

void MovieSearchEngine::addStrategy(std::unique_ptr<SearchStrategy> strategy) {
    strategies.push_back(std::move(strategy));
}

std::vector<Movie> MovieSearchEngine::search(const std::string& query) {
    std::vector<Movie> results;

    for (const auto& strategy : strategies) {
        auto strategyResults = strategy->search(movies, query);
        results.insert(results.end(), strategyResults.begin(), strategyResults.end());
    }

    // Removing duplicates (optional)
    std::sort(results.begin(), results.end(), [](const Movie& a, const Movie& b) {
        return a.imdb_id < b.imdb_id;
    });
    results.erase(std::unique(results.begin(), results.end(), [](const Movie& a, const Movie& b) {
        return a.imdb_id == b.imdb_id;
    }), results.end());

    return results;
}

int MovieSearchEngine::calculateRelevance(const Movie& movie, const std::string& query) {
    // Implement relevance calculation if needed
    return 0;
}

std::vector<Movie> TitleSearch::search(const std::vector<Movie>& movies, const std::string& query) {
    std::vector<Movie> results;
    for (const auto& movie : movies) {
        if (movie.title.find(query) != std::string::npos) {
            results.push_back(movie);
        }
    }
    return results;
}

std::vector<Movie> TagSearch::search(const std::vector<Movie>& movies, const std::string& query) {
    std::vector<Movie> results;
    for (const auto& movie : movies) {
        if (movie.tags.find(query) != std::string::npos) {
            results.push_back(movie);
        }
    }
    return results;
}

std::vector<Movie> PlotSearch::search(const std::vector<Movie>& movies, const std::string& query) {
    std::vector<Movie> results;
    for (const auto& movie : movies) {
        if (movie.plot_synopsis.find(query) != std::string::npos) {
            results.push_back(movie);
        }
    }
    return results;
}
