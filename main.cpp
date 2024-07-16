#include <iostream>
#include <fstream>
#include <sstream>
#include <httplib.h>
#include "external\json\single_include\nlohmann\json.hpp"
#include "MovieSearch.h"
#include "MovieSearch.cpp"

using namespace std;
using json = nlohmann::json;

string read_file(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        throw runtime_error("No se pudo abrir el archivo: " + path);
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void handle_search(const httplib::Request& req, httplib::Response& res) {
    try {
        string query = req.get_param_value("query");
        Buscador& engine = Buscador::getInstance();
        auto result = engine.buscar(query);

        nlohmann::json jsonResponse;
        for (const auto& movie : result) {
            jsonResponse.push_back({
                                           {"imdb_id", movie.imdb_id},
                                           {"title", movie.title},
                                           {"plot_synopsis", movie.plot_synopsis},
                                           {"tags", movie.tags},
                                           {"split", movie.split},
                                           {"synopsis_source", movie.synopsis_source}
                                   });
        }

        res.set_content(jsonResponse.dump(), "application/json");
    } catch (const std::exception& e) {
        res.status = 500;
        res.set_content("Error interno del servidor: " + std::string(e.what()), "text/plain");
    }
}


void handle_load_movies(const httplib::Request& req, httplib::Response& res) {
    Buscador& engine = Buscador::getInstance();

    try {
        engine.loadCSV("C:/Users/Renat/CLionProjects/Proyecto-Programacion-III/peliculas.csv");
        //engine.loadCSV("C:/Users/sofia/Desktop/Documentos/2024/progra 3/Proyecto-Programacion-III/peliculas.csv");
        res.set_content("Carga de películas exitosa", "text/plain");
    } catch (const exception& e) {
        res.set_content("Error al cargar CSV: " + string(e.what()), "text/plain");
    }
}

int main() {
    Buscador &engine = Buscador::getInstance();
    try {
        engine.loadCSV("C:/Users/Renat/CLionProjects/Proyecto-Programacion-III/peliculas.csv");
        //engine.loadCSV("C:/Users/sofia/Desktop/Documentos/2024/progra 3/Proyecto-Programacion-III/peliculas.csv");
    } catch (const exception &e) {
        cout << "Error cargando CSV: " << e.what() << endl;
        return 1;
    }
    engine.addEstrategia(make_unique<PorTitulo>());
    engine.addEstrategia(make_unique<PorTag>());
    engine.addEstrategia(make_unique<PorPlot>());

    httplib::Server svr;

    svr.Get("/", [](const httplib::Request &, httplib::Response &res) {
        string html = read_file("../web/index.html");
        res.set_content(html, "text/html");
    });

    svr.Get("/styles.css", [](const httplib::Request &, httplib::Response &res) {
        string css = read_file("../web/styles.css");
        res.set_content(css, "text/css");
    });

    svr.Get("/script.js", [](const httplib::Request &, httplib::Response &res) {
        string js = read_file("../web/script.js");
        res.set_content(js, "application/javascript");
    });

    svr.Get("/auth/login", [](const httplib::Request &, httplib::Response &res) {
        string html = read_file("../web/auth/login.html");
        res.set_content(html, "text/html");
    });

    svr.Get("/auth/login.css", [](const httplib::Request &, httplib::Response &res) {
        string css = read_file("../web/auth/login.css");
        res.set_content(css, "text/css");
    });

    svr.Get("/auth/login.js", [](const httplib::Request &, httplib::Response &res) {
        string js = read_file("../web/auth/login.js");
        res.set_content(js, "application/javascript");
    });

    svr.Get("/auth/register", [](const httplib::Request &, httplib::Response &res) {
        string html = read_file("../web/auth/register.html");
        res.set_content(html, "text/html");
    });

    svr.Get("/auth/register.css", [](const httplib::Request &, httplib::Response &res) {
        string css = read_file("../web/auth/register.css");
        res.set_content(css, "text/css");
    });

    svr.Get("/auth/register.js", [](const httplib::Request &, httplib::Response &res) {
        string js = read_file("../web/auth/register.js");
        res.set_content(js, "application/javascript");
    });

    svr.Get("/browse", [](const httplib::Request &, httplib::Response &res) {
        string html = read_file("../web/browse.html");
        res.set_content(html, "text/html");
    });

    svr.Get("/browse.css", [](const httplib::Request &, httplib::Response &res) {
        string css = read_file("../web/browse.css");
        res.set_content(css, "text/css");
    });

    svr.Get("/browse.js", [](const httplib::Request &, httplib::Response &res) {
        string js = read_file("../web/browse.js");
        res.set_content(js, "application/javascript");
    });

    svr.Get("/liked", [](const httplib::Request &, httplib::Response &res) {
        string html = read_file("../web/liked.html");
        res.set_content(html, "text/html");
    });

    svr.Get("/liked.css", [](const httplib::Request &, httplib::Response &res) {
        string css = read_file("../web/liked.css");
        res.set_content(css, "text/css");
    });

    svr.Get("/liked.js", [](const httplib::Request &, httplib::Response &res) {
        string js = read_file("../web/liked.js");
        res.set_content(js, "application/javascript");
    });

    svr.Get("/later", [](const httplib::Request &, httplib::Response &res) {
        string html = read_file("../web/later.html");
        res.set_content(html, "text/html");
    });

    svr.Get("/later.css", [](const httplib::Request &, httplib::Response &res) {
        string css = read_file("../web/later.css");
        res.set_content(css, "text/css");
    });

    svr.Get("/later.js", [](const httplib::Request &, httplib::Response &res) {
        string js = read_file("../web/later.js");
        res.set_content(js, "application/javascript");
    });

    svr.Get("/search", handle_search);
    svr.Get("/load_movies", handle_load_movies);

    svr.listen("localhost", 8080);

    return 0;
}
