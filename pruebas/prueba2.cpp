#include "MovieSearch.h"
#include <iostream>

int main() {
    MovieSearchEngine& engine = MovieSearchEngine::getInstance();
    engine.loadMovies("C:/Users/sofia/Desktop/Documentos/2024/progra 3/proyecto-prueba/prueba.csv");

    engine.addStrategy(std::make_unique<TitleSearch>());
    engine.addStrategy(std::make_unique<TagSearch>());
    engine.addStrategy(std::make_unique<PlotSearch>());

    std::string query;
    std::cout << "Enter search query: ";
    std::cin >> query;

    auto results = engine.search(query);

    std::cout << "Search results for query: " << query << std::endl;

    for (const auto& movie : results) {
        std::cout << "IMDB ID: " << movie.imdb_id << "\n"
                  << "Title: " << movie.title << "\n"
                  << "Tags: " << movie.tags << "\n\n";
    }

    return 0;
}
