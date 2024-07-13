#ifndef PROYECTO_PRUEBA_MOVIESEARCH_H
#define PROYECTO_PRUEBA_MOVIESEARCH_H

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <memory>

class Movie {
public:
    std::string imdb_id;
    std::string title;
    std::string plot_synopsis;
    std::string tags;
    std::string split;
    std::string synopsis_source;

    Movie(const std::string& id, const std::string& t, const std::string& plot, const std::string& tag, const std::string& sp, const std::string& source)
            : imdb_id(id), title(t), plot_synopsis(plot), tags(tag), split(sp), synopsis_source(source) {}

    bool operator<(const Movie& other) const {
        return imdb_id < other.imdb_id;
    }
};

class SearchStrategy {
public:
    virtual std::vector<Movie> search(const std::vector<Movie>& movies, const std::string& query) = 0;
};

class TitleSearch : public SearchStrategy {
public:
    std::vector<Movie> search(const std::vector<Movie>& movies, const std::string& query) override;
};

class TagSearch : public SearchStrategy {
public:
    std::vector<Movie> search(const std::vector<Movie>& movies, const std::string& query) override;
};

class PlotSearch : public SearchStrategy {
public:
    std::vector<Movie> search(const std::vector<Movie>& movies, const std::string& query) override;
};

class MovieSearchEngine {
private:
    std::vector<Movie> movies;
    std::vector<std::unique_ptr<SearchStrategy>> strategies;
    std::priority_queue<std::pair<int, Movie>> searchResults;
    std::mutex resultMutex;

    MovieSearchEngine() = default;
    int calculateRelevance(const Movie& movie, const std::string& query);

public:
    static MovieSearchEngine& getInstance();
    void addStrategy(std::unique_ptr<SearchStrategy> strategy);
    std::vector<Movie> search(const std::string& query);
    void loadMovies(const std::string& filePath);
};

#endif //PROYECTO_PRUEBA_MOVIESEARCH_H
