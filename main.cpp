#include <httplib.h>
#include "ALL.h"
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
int main() {
    httplib::Server svr;

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
