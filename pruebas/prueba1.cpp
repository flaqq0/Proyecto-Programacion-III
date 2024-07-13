#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <thread>
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

    Movie(string i, string t, string p, string ta, string s, string ss) : imdb_id(i), title(t), plot_synopsis(p), tags(ta), split(s), synopsis_source(ss) {}
};

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    vector<Movie*> movies;
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(Movie* movie) {
        TrieNode* node = root;
        for (char c : movie->title) {
            if (!node->children.count(c)) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->movies.push_back(movie);
    }

    vector<Movie*> search(string query) {
        TrieNode* node = root;
        for (char c : query) {
            if (!node->children.count(c)) {
                return {};
            }
            node = node->children[c];
        }
        return node->movies;
    }
};

class PriorityQueue {
private:
    priority_queue<pair<int, Movie*>> pq;
    mutex mtx;

public:
    void push(int score, Movie* movie) {
        lock_guard<mutex> lock(mtx);
        pq.push({-score, movie});
    }

    pair<int, Movie*> top() {
        lock_guard<mutex> lock(mtx);
        return pq.top();
    }

    void pop() {
        lock_guard<mutex> lock(mtx);
        pq.pop();
    }

    bool empty() {
        lock_guard<mutex> lock(mtx);
        return pq.empty();
    }
};

void recommendMovies(string searching, Trie& trie, PriorityQueue& pq) {
    vector<Movie*> movies = trie.search(searching);
    for (Movie* movie : movies) {
        int score = 0;
        if (movie->title.find(searching) != string::npos) {
            score += 10;
        }
        if (movie->plot_synopsis.find(searching) != string::npos) {
            score += 5;
        }
        if (movie->tags.find(searching) != string::npos) {
            score += 3;
        }
        pq.push(score, movie);
    }
}

int main() {
    ifstream file("C:/Users/sofia/Desktop/Documentos/2024/progra 3/proyecto-prueba/prueba.csv");
    string line;
    getline(file, line);
    Trie trie;
    while (getline(file, line)) {
        size_t pos = line.find(';');
        string imdb_id = line.substr(0, pos);
        line = line.substr(pos + 1);
        pos = line.find(';');
        string title = line.substr(0, pos);
        line = line.substr(pos + 1);
        pos = line.find(';');
        string plot_synopsis = line.substr(0, pos);
        line = line.substr(pos + 1);
        pos = line.find(';');
        string tags = line.substr(0, pos);
        string synopsis_source = line.substr(pos + 1);
        Movie* movie = new Movie(imdb_id, title, plot_synopsis, tags, synopsis_source, synopsis_source);
        trie.insert(movie);
    }
    file.close();

    cout << "buscar: ";
    string searching;
    getline(cin, searching);

    PriorityQueue pq;
    vector<thread> threads;
    for (int i = 0; i < 4; i++) {
        threads.emplace_back(recommendMovies, searching, ref(trie), ref(pq));
    }
    for (auto& thread : threads) {
        thread.join();
    }

    cout << "Top 5 recommended movies:" << endl;
    for (int i = 0; i < 5 && !pq.empty(); i++) {
        Movie* movie = pq.top().second;
        cout << movie->title << " (" << movie->imdb_id << "): " << endl;
        pq.pop();
    }
    return 0;
}