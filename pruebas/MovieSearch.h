#ifndef PROYECTO_PRUEBA_MOVIESEARCH_H
#define PROYECTO_PRUEBA_MOVIESEARCH_H

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <thread>
#include <mutex>
#include <memory>
#include <iostream>
#include <algorithm>
#include <stack>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <regex>
#include <future>

using namespace std;

class Movie {
public:
    string imdb_id;
    string title;
    string plot_synopsis;
    string tags;
    string split;
    string synopsis_source;

    Movie() = default;

    Movie(const string& id, const string& t, const string& plot, const string& tag, const string& sp, const string& source)
            : imdb_id(id), title(t), plot_synopsis(plot), tags(tag), split(sp), synopsis_source(source) {}

    bool operator<(const Movie& other) const {
        return imdb_id < other.imdb_id;
    }
};

class TrieNode {
public:
    unordered_map<char, shared_ptr<TrieNode>> children;
    vector<Movie> movies;
    bool endWord;

    TrieNode() : endWord(false) {}
};

class Trie {
private:
    shared_ptr<TrieNode> root;

public:
    Trie() : root(make_shared<TrieNode>()) {}

    void insert(const string& word, const Movie& movie);

    vector<Movie> search(const string& query);

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
    unordered_map<string, Movie> movieMap;
    vector<unique_ptr<Estrategia>> strategies;
    Trie titleTrie;
    Trie tagTrie;
    Trie plotTrie;

    Buscador() = default;
    int calcularRelevancia(const Movie& movie, const string& query);

public:
    static Buscador& getInstance();
    void addEstrategia(unique_ptr<Estrategia> estrategia);
    vector<Movie> buscar(const string& query);
    void loadCSV(const string& path);

    template<typename T>
    int contador(const T& text, const T& word);
};

#endif //PROYECTO_PRUEBA_MOVIESEARCH_H
