#ifndef PROYECTO_PRUEBA_MOVIESEARCH_H
#define PROYECTO_PRUEBA_MOVIESEARCH_H

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <memory>
#include "external/json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;
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

class Estrategia {
public:
    virtual vector<Movie> search(const vector<Movie>& movies, const string& query) = 0;
};

class PorTitulo : public Estrategia {
public:
    vector<Movie> search(const vector<Movie>& movies, const string& query) override;
};

class PorTag : public Estrategia {
public:
    vector<Movie> search(const vector<Movie>& movies, const string& query) override;
};

class PorPlot : public Estrategia {
public:
    vector<Movie> search(const vector<Movie>& movies, const string& query) override;
};

class Buscador {
private:
    vector<Movie> movies;
    vector<unique_ptr<Estrategia>> strategies;
    priority_queue<pair<int, Movie>> searchResults;
    mutex resultMutex;

    Buscador() = default;
    int calcularRelevancia(const Movie& movie, const string& query);

public:
    static Buscador& getInstance();
    void addEstrategia(unique_ptr<Estrategia> strategy);
    vector<Movie> buscar(const string& query);
    void loadMovies(const string& filePath);
    void loadCSV(const string& filePath);
    int contador(const string& text, const string& word);
};

#endif //PROYECTO_PRUEBA_MOVIESEARCH_H
