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

// Define your Movie structure
struct Movie {
    std::string imdb_id;
    std::string title;
    std::string plot_synopsis;
    std::string tags;
    std::string split;
    std::string synopsis_source;

    // Constructor
    Movie(const std::string& id, const std::string& t, const std::string& plot,
          const std::string& tg, const std::string& sp, const std::string& src)
            : imdb_id(id), title(t), plot_synopsis(plot), tags(tg), split(sp), synopsis_source(src) {}
};

// Define your binary search tree node
struct BSTNode {
    Movie movie;
    int relevance;
    BSTNode* left;
    BSTNode* right;

    // Constructor
    BSTNode(const Movie& m, int rel)
            : movie(m), relevance(rel), left(nullptr), right(nullptr) {}
};

// Comparator for priority queue (min-heap based on relevance)
struct CompareRelevance {
    bool operator()(const BSTNode* lhs, const BSTNode* rhs) const {
        return lhs->relevance < rhs->relevance;
    }
};

class MovieSearchEngine {
private:
    std::vector<Movie> movies;
    std::priority_queue<BSTNode*, std::vector<BSTNode*>, CompareRelevance> pq;
    std::mutex mtx;

public:
    // Singleton instance
    static MovieSearchEngine& getInstance() {
        static MovieSearchEngine instance;
        return instance;
    }

    // Load movies from CSV
    void loadMovies(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filePath << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string imdb_id, title, plot_synopsis, tags, split, synopsis_source;

            if (std::getline(ss, imdb_id, ';') &&
                std::getline(ss, title, ';') &&
                std::getline(ss, plot_synopsis, ';') &&
                std::getline(ss, tags, ';') &&
                std::getline(ss, split, ';') &&
                std::getline(ss, synopsis_source, ';')) {

                Movie movie(imdb_id, title, plot_synopsis, tags, split, synopsis_source);
                movies.push_back(movie);

                // Debug print to verify movie loading
                std::cout << "Loaded movie: " << title << std::endl;
            } else {
                std::cerr << "Error parsing line: " << line << std::endl;
            }
        }

        file.close();
    }

    // Search movies based on query
    std::vector<Movie> search(const std::string& query) {
        std::vector<Movie> results;

        // Start threads to calculate relevance concurrently
        std::vector<std::thread> threads;
        int numThreads = 4; // Adjust the number of threads as needed
        int moviesPerThread = movies.size() / numThreads;
        for (int i = 0; i < numThreads; ++i) {
            int start = i * moviesPerThread;
            int end = (i == numThreads - 1) ? movies.size() : (i + 1) * moviesPerThread;
            threads.emplace_back(&MovieSearchEngine::processMovies, this, std::ref(query), start, end);
        }

        // Join threads
        for (auto& thread : threads) {
            thread.join();
        }

        // Collect top 5 most relevant movies from the priority queue
        int count = 0;
        while (!pq.empty() && count < 5) {
            BSTNode* node = pq.top();
            results.push_back(node->movie);
            pq.pop();
            ++count;
        }

        return results;
    }

    // Get top 5 most relevant movies
    std::vector<Movie> getTop5Movies() {
        std::vector<Movie> top5;
        std::priority_queue<BSTNode*, std::vector<BSTNode*>, CompareRelevance> tempQueue = pq;

        int count = 0;
        while (!tempQueue.empty() && count < 5) {
            BSTNode* node = tempQueue.top();
            top5.push_back(node->movie);
            tempQueue.pop();
            ++count;
        }

        return top5;
    }

private:
    // Calculate relevance for a movie based on query
    int calculateRelevance(const Movie& movie, const std::string& query) {
        int relevance = 0;

        // Example: Simple relevance calculation (customize based on your requirements)
        if (movie.title.find(query) != std::string::npos) {
            relevance += 3; // Higher weight for matching in title
        }
        if (movie.tags.find(query) != std::string::npos) {
            relevance += 2;
        }
        if (movie.plot_synopsis.find(query) != std::string::npos) {
            relevance += 1;
        }

        return relevance;
    }

    // Process movies to calculate relevance and insert into BST
    void processMovies(const std::string& query, int start, int end) {
        for (int i = start; i < end; ++i) {
            int relevance = calculateRelevance(movies[i], query);
            BSTNode* node = new BSTNode(movies[i], relevance);

            // Insert into priority queue (min-heap) in a thread-safe manner
            std::lock_guard<std::mutex> lock(mtx);
            pq.push(node);
        }
    }

};

int main() {
    // Example usage
    MovieSearchEngine& engine = MovieSearchEngine::getInstance();
    engine.loadMovies("C:/Users/sofia/Desktop/Documentos/2024/progra 3/proyecto-prueba/prueba.csv");

    // Example search
    std::string query;
    std::cout << "Enter search query: ";
    std::cin >> query;
    std::vector<Movie> searchResults = engine.search(query);

    // Get top 5 most relevant movies
    std::vector<Movie> top5 = engine.getTop5Movies();

    // Output the top 5 most relevant movies
    std::cout << "Top 5 most relevant movies for query '" << query << "':" << std::endl;
    for (const auto& movie : top5) {
        std::cout << "Title: " << movie.title << std::endl;
    }

    return 0;
}
