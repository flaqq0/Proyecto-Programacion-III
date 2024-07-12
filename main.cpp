#include <httplib.h>
#include "ALL.h"
string read_file(const string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + path);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
int main() {
    string fil = "C:/Users/Usuario/Desktop/Utec/2024-1/PrograIII/ProyectoLimpio/peliculas.csv";
    vector<CMovie> movies = loadCsv(fil);
    /*
    for (int i = 0; i < 1; i++) {
        cout << "ID :" << movies[i].imdb_id << endl;
        cout << "TITTLE :" << movies[i].title << endl;
        cout << "PLOT SYNOPSIS :" << movies[i].plot_synopsis << endl;
        cout << "TAGS :" << movies[i].tags << endl;
        cout << "SPLIT :" << movies[i].split << endl;
        cout << "SYNOPSIS SOURCE:" << movies[i].synopsis_source << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    }*/

    Premium premium("Premium", 44.90,"La mejor","4k(Ultra HD) + HDR", true, 4, 6);
    Standard standard("Estándard",34.90,"Excelente","1080p (Full HD)",false,2,2);
    Basic basic("Básico",24.90,"Buena","720p (HD)", false,1,1);

    httplib::Server svr;

    svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
        std::string html = read_file("../web/index.html");
        res.set_content(html, "text/html");
    });
    svr.Get("/styles.css", [](const httplib::Request&, httplib::Response& res) {
        std::string css = read_file("../web/styles.css");
        res.set_content(css, "text/css");
    });
    svr.Get("/script.js", [](const httplib::Request&, httplib::Response& res) {
        std::string js = read_file("../web/script.js");
        res.set_content(js, "application/javascript");
    });

    svr.listen("localhost", 8080);
    return 0;
}
