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

    svr.Get("/auth/login", [](const httplib::Request&, httplib::Response& res) {
        std::string html = read_file("../web/auth/login.html");
        res.set_content(html, "text/html");
    });
    svr.Get("/auth/login.css", [](const httplib::Request&, httplib::Response& res) {
        std::string css = read_file("../web/auth/login.css");
        res.set_content(css, "text/css");
    });
    svr.Get("/auth/login.js", [](const httplib::Request&, httplib::Response& res) {
        std::string js = read_file("../web/auth/login.js");
        res.set_content(js, "application/javascript");
    });

    svr.Get("/auth/register", [](const httplib::Request&, httplib::Response& res) {
        std::string html = read_file("../web/auth/register.html");
        res.set_content(html, "text/html");
    });
    svr.Get("/auth/register.css", [](const httplib::Request&, httplib::Response& res) {
        std::string css = read_file("../web/auth/register.css");
        res.set_content(css, "text/css");
    });
    svr.Get("/auth/register.js", [](const httplib::Request&, httplib::Response& res) {
        std::string js = read_file("../web/auth/register.js");
        res.set_content(js, "application/javascript");
    });


    svr.listen("localhost", 8080);
    return 0;
}
