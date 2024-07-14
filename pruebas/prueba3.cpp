#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <mutex>
#include <thread>
#include <queue>
using namespace std;
struct Movie {
    string imdb_id;
    string title;
    string plot_synopsis;
    string tags;
    string split;
    string synopsis_source;

    Movie(const string& id, const string& t, const string& plot,
          const string& tg, const string& sp, const string& src)
            : imdb_id(id), title(t), plot_synopsis(plot), tags(tg), split(sp), synopsis_source(src) {}
};

struct BSTNode {
    Movie movie;
    int relevance;
    BSTNode* left;
    BSTNode* right;

    BSTNode(const Movie& m, int rel)
            : movie(m), relevance(rel), left(nullptr), right(nullptr) {}
};

struct CompareRelevance {
    bool operator()(const BSTNode* lhs, const BSTNode* rhs) const {
        return lhs->relevance < rhs->relevance;
    }
};

class MovieSearchEngine {
private:
    vector<Movie> movies;
    priority_queue<BSTNode*, vector<BSTNode*>, CompareRelevance> pq;
    mutex mtx;

public:
    static MovieSearchEngine& getInstance() {
        static MovieSearchEngine instance;
        return instance;
    }

    void loadMovies(const string& filePath) {
        ifstream file(filePath);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filePath << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string imdb_id, title, plot_synopsis, tags, split, synopsis_source;

            if (getline(ss, imdb_id, ';') &&
                getline(ss, title, ';') &&
                getline(ss, plot_synopsis, ';') &&
                getline(ss, tags, ';') &&
                getline(ss, split, ';') &&
                getline(ss, synopsis_source, ';')) {

                Movie movie(imdb_id, title, plot_synopsis, tags, split, synopsis_source);
                movies.push_back(movie);

                cout << "Loaded movie: " << title << endl;
            } else {
                cerr << "Error parsing line: " << line << endl;
            }
        }

        file.close();
    }

    vector<Movie> search(const string& query) {
        vector<Movie> results;

        vector<thread> threads;
        int numThreads = 4;
        int moviesPerThread = movies.size() / numThreads;
        for (int i = 0; i < numThreads; ++i) {
            int start = i * moviesPerThread;
            int end = (i == numThreads - 1) ? movies.size() : (i + 1) * moviesPerThread;
            threads.emplace_back(&MovieSearchEngine::processMovies, this, ref(query), start, end);
        }

        for (auto& thread : threads) {
            thread.join();
        }

        int count = 0;
        while (!pq.empty() && count < 5) {
            BSTNode* node = pq.top();
            results.push_back(node->movie);
            pq.pop();
            ++count;
        }

        return results;
    }

private:
    int calculateRelevance(const Movie& movie, const string& query) {
        int relevance = 0;

        if (movie.title.find(query) != string::npos) {
            relevance += 3;
        }
        if (movie.tags.find(query) != string::npos) {
            relevance += 2;
        }
        if (movie.plot_synopsis.find(query) != string::npos) {
            relevance += 1;
        }

        return relevance;
    }

    void processMovies(const string& query, int start, int end) {
        for (int i = start; i < end; ++i) {
            int relevance = calculateRelevance(movies[i], query);
            BSTNode* node = new BSTNode(movies[i], relevance);

            lock_guard<mutex> lock(mtx);
            pq.push(node);
        }
    }
};

int main() {
    MovieSearchEngine& engine = MovieSearchEngine::getInstance();
    engine.loadMovies("C:/Users/sofia/Desktop/Documentos/2024/progra 3/proyecto-prueba/prueba.csv");

    string query;
    cout << "Enter buscar query: ";
    cin >> query;
    vector<Movie> searchResults = engine.search(query);

    for (const auto& movie : searchResults) {
        cout << "Title: " << movie.title << endl;
    }

    return 0;
}
