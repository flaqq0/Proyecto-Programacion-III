#ifndef PROYECTO_PRUEBA_MOVIESEARCH_H
#define PROYECTO_PRUEBA_MOVIESEARCH_H

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <memory>
using namespace std;

class Movie {
public:
    string imdb_id;
    string title;
    string plot_synopsis;
    string tags;
    string split;
    string synopsis_source;

    Movie(const string& id, const string& t, const string& plot, const string& tag, const string& sp, const string& source)
            : imdb_id(id), title(t), plot_synopsis(plot), tags(tag), split(sp), synopsis_source(source) {}

    bool operator<(const Movie& other) const {
        return imdb_id < other.imdb_id;
    }
};

// Clase genérica para tipo de búsqueda
template <typename T>
class SearchStrategy {
public:
    virtual vector<T> search(const vector<T>& items, const string& query) = 0;
};

//búsqueda por título
class TitleSearch : public SearchStrategy<Movie> {
public:
    vector<Movie> search(const vector<Movie>& movies, const string& query) override;
};

//búsqueda por tag
class TagSearch : public SearchStrategy<Movie> {
public:
    vector<Movie> search(const vector<Movie>& movies, const string& query) override;
};

//búsqueda por sinopsis
class PlotSearch : public SearchStrategy<Movie> {
public:
    vector<Movie> search(const vector<Movie>& movies, const string& query) override;
};

//búsqueda de películas
class MovieSearchEngine {
private:
    vector<Movie> movies;
    vector<unique_ptr<SearchStrategy<Movie>>> strategies;
    priority_queue<pair<int, Movie>> searchResults;
    mutex resultMutex;

    MovieSearchEngine() = default;
    int calculateRelevance(const Movie& movie, const string& query);

public:
    static MovieSearchEngine& getInstance();
    void addStrategy(unique_ptr<SearchStrategy<Movie>> strategy);
    vector<Movie> search(const string& query);
    void loadMovies(const string& filePath);
};

#endif //PROYECTO_PRUEBA_MOVIESEARCH_H

