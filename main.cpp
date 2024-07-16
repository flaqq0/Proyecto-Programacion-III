#include <iostream>
#include <fstream>
#include <sstream>
#include <httplib.h>
#include "MovieSearch.h"
#include "MovieSearch.cpp"

using namespace std;

string read_file(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + path);
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Función para manejar la búsqueda de películas
void handle_search(const httplib::Request& req, httplib::Response& res) {
    string query = req.get_param_value("query");
    int page = stoi(req.get_param_value("page", 1));
    int page_size = stoi(req.get_param_value("page_size", 10));

    Buscador& engine = Buscador::getInstance();
    auto result = engine.buscar(query);

    int start_index = (page - 1) * page_size;
    int end_index = std::min(start_index + page_size, static_cast<int>(result.size()));

    std::stringstream json_response;
    json_response << "[";
    for (int i = start_index; i < end_index; ++i) {
        const auto& movie = result[i];
        json_response << "{"
                      << "\"title\":\"" << movie.title << "\","
                      << "\"tags\":\"" << movie.tags << "\""
                      << "}";
        if (i != end_index - 1) {
            json_response << ",";
        }
    }
    json_response << "]";

    res.set_content(json_response.str(), "application/json");
}


// Función para cargar películas desde CSV
void handle_load_movies(const httplib::Request& req, httplib::Response& res) {
    Buscador& engine = Buscador::getInstance();

    try {
        engine.loadCSV("C:/Users/Usuario/Desktop/Utec/2024-1/PrograIII/PROYECTOFINAL/Proyecto-Programacion-III/peliculas.csv");
        res.set_content("Carga de películas exitosa", "text/plain");
    } catch (const exception& e) {
        res.set_content("Error al cargar CSV: " + string(e.what()), "text/plain");
    }
}

int main() {
    Buscador& engine = Buscador::getInstance();
    try {
        engine.loadCSV("C:/Users/Usuario/Desktop/Utec/2024-1/PrograIII/PROYECTOFINAL/Proyecto-Programacion-III/peliculas.csv");
    } catch (const exception& e) {
        cout << "Error loading CSV: " << e.what() << endl;
        return 1;
    }
    engine.addEstrategia(make_unique<PorTitulo>());
    engine.addEstrategia(make_unique<PorTag>());
    engine.addEstrategia(make_unique<PorPlot>());

    // Iniciar servidor HTTP
    httplib::Server svr;

    // Configurar rutas estáticas
    svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
        string html = read_file("../web/index.html");
        res.set_content(html, "text/html");
    });

    svr.Get("/styles.css", [](const httplib::Request&, httplib::Response& res) {
        string css = read_file("../web/styles.css");
        res.set_content(css, "text/css");
    });

    svr.Get("/script.js", [](const httplib::Request&, httplib::Response& res) {
        string js = read_file("../web/script.js");
        res.set_content(js, "application/javascript");
    });

    svr.Get("/auth/login", [](const httplib::Request&, httplib::Response& res) {
        string html = read_file("../web/auth/login.html");
        res.set_content(html, "text/html");
    });

    svr.Get("/auth/login.css", [](const httplib::Request&, httplib::Response& res) {
        string css = read_file("../web/auth/login.css");
        res.set_content(css, "text/css");
    });

    svr.Get("/auth/login.js", [](const httplib::Request&, httplib::Response& res) {
        string js = read_file("../web/auth/login.js");
        res.set_content(js, "application/javascript");
    });

    svr.Get("/auth/register", [](const httplib::Request&, httplib::Response& res) {
        string html = read_file("../web/auth/register.html");
        res.set_content(html, "text/html");
    });

    svr.Get("/auth/register.css", [](const httplib::Request&, httplib::Response& res) {
        string css = read_file("../web/auth/register.css");
        res.set_content(css, "text/css");
    });

    svr.Get("/auth/register.js", [](const httplib::Request&, httplib::Response& res) {
        string js = read_file("../web/auth/register.js");
        res.set_content(js, "application/javascript");
    });

    svr.Get("/browse", [](const httplib::Request&, httplib::Response& res) {
        string html = read_file("../web/browse.html");
        res.set_content(html, "text/html");
    });

    svr.Get("/browse.css", [](const httplib::Request&, httplib::Response& res) {
        string css = read_file("../web/browse.css");
        res.set_content(css, "text/css");
    });

    svr.Get("/browse.js", [](const httplib::Request&, httplib::Response& res) {
        string js = read_file("../web/browse.js");
        res.set_content(js, "application/javascript");
    });

    svr.listen("localhost", 8080);

    return 0;
}

