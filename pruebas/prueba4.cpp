#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <functional>
#include <fstream>
#include <sstream>
#include <thread>
#include <unordered_map>
#include <algorithm>
#include <mutex>
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
};

class MovieDatabase {
private:
    vector<Movie> movies;
    mutex mtx;
    static MovieDatabase* instance;
    MovieDatabase() {}

public:
    static MovieDatabase* getInstance() {
        if (instance == nullptr) {
            instance = new MovieDatabase();
        }
        return instance;
    }

    void loadMovies(const string& filename) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            istringstream stream(line);
            string id, title, plot, tags, split, source;
            getline(stream, id, ';');
            getline(stream, title, ';');
            getline(stream, plot, ';');
            getline(stream, tags, ';');
            getline(stream, split, ';');
            getline(stream, source, ';');
            movies.emplace_back(id, title, plot, tags, split, source);
        }
    }

    const vector<Movie>& getMovies() const {
        return movies;
    }
};

MovieDatabase* MovieDatabase::instance = nullptr;

struct CompareMovies {
    bool operator()(const pair<int, Movie>& lhs, const pair<int, Movie>& rhs) {
        return lhs.first < rhs.first;
    }
};

class MovieSearcher {
public:
    vector<Movie> search(const string& query, int topN) {
        auto& movies = MovieDatabase::getInstance()->getMovies();
        priority_queue<pair<int, Movie>, vector<pair<int, Movie>>, CompareMovies> pq;

        mutex mtx;
        vector<thread> threads;
        for (const auto& movie : movies) {
            threads.emplace_back([&, movie]() {
                int relevance = computeRelevance(movie, query);
                lock_guard<mutex> lock(mtx);
                pq.push({relevance, movie});
                if (pq.size() > topN) {
                    pq.pop();
                }
            });
        }

        for (auto& t : threads) {
            t.join();
        }

        vector<Movie> result;
        while (!pq.empty()) {
            result.push_back(pq.top().second);
            pq.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }

private:
    int computeRelevance(const Movie& movie, const string& query) {
        int relevance = 0;
        relevance += countOccurrences(movie.title, query) * 3;
        relevance += countOccurrences(movie.tags, query) * 2;
        relevance += countOccurrences(movie.plot_synopsis, query);
        return relevance;
    }

    int countOccurrences(const string& text, const string& word) {
        int count = 0;
        size_t pos = text.find(word, 0);
        while (pos != string::npos) {
            ++count;
            pos = text.find(word, pos + word.length());
        }
        return count;
    }
};

int main() {
    MovieDatabase* db = MovieDatabase::getInstance();
    db->loadMovies("C:/Users/sofia/Desktop/Documentos/2024/progra 3/proyecto-prueba/prueba.csv");

    MovieSearcher searcher;
    string query;
    cout << "Buscar: "; cin >> query;
    auto results = searcher.search(query, 5);

    for (const auto& movie : results) {
        cout << "Title: " << movie.title <<endl<< "Tags: " << movie.tags << "\n\n";
    }

    return 0;
}

