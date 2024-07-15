#include "MovieSearch.h"
using namespace std;

void Trie::insert(const string& word, const Movie& movie) {
    auto node = root;
    for (const char& ch : word) {
        char lower_ch = tolower(ch);
        if (!node->children.count(lower_ch)) {
            node->children[lower_ch] = make_shared<TrieNode>();
        }
        node = node->children[lower_ch];
    }
    node->endWord = true;
    node->movies.push_back(movie);
}

vector<Movie> Trie::search(const string& query) {
    vector<Movie> result;
    auto node = root;
    for (const char& ch : query) {
        char lower_ch = tolower(ch);
        if (!node->children.count(lower_ch)) {
            return {}; // No match found
        }
        node = node->children[lower_ch];
    }
    if (node->endWord) {
        result.insert(result.end(), node->movies.begin(), node->movies.end());
    }

    stack<shared_ptr<TrieNode>> stack;
    stack.push(node);
    while (!stack.empty()) {
        auto currentNode = stack.top();
        stack.pop();
        if (currentNode->endWord) {
            result.insert(result.end(), currentNode->movies.begin(), currentNode->movies.end());
        }
        for (const auto& child : currentNode->children) {
            stack.push(child.second);
        }
    }

    return result;
}

Buscador& Buscador::getInstance() {
    static Buscador instance;
    return instance;
}

string trim(const string& s) {
    size_t a = s.find_first_not_of(' ');
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(' ');
    return s.substr(a, (b - a + 1));
}

vector<string> splitLinea(const string &l) {
    vector<string> res;
    stringstream ll(l);
    string lll;
    bool comillas = false;
    char c;
    string actual;

    while (ll.get(c)) {
        if (c == '"' && (actual.empty() || actual.back() != '\\')) {
            comillas = !comillas;
        }else if (c == ',' && !comillas) {
            res.push_back(trim(actual));
            actual.clear();
        } else { actual += c;}
    }
    res.push_back(trim(actual));

    return res;
}

Movie asignar (const string &linea) {
    vector<string> fields = splitLinea(linea);
    Movie movie;

    if (fields.size() >= 6) {
        movie.imdb_id = fields[0];
        movie.title = fields[1];
        movie.plot_synopsis = fields[2];
        movie.tags = fields[3];
        movie.split = fields[4];
        movie.synopsis_source = fields[5];
    }

    return movie;
}

vector<Movie> readCSV(const string& path) {
    vector<Movie> movies;
    ifstream file(path);
    string linea;
    string combl;
    regex imdb_id_pattern(R"(^tt\d{7})");

    getline(file, linea);

    while (getline(file, linea)) {
        if (regex_search(linea, imdb_id_pattern)) {
            if (!combl.empty()) {
                movies.push_back(asignar(combl));
                combl.clear();
            }
        }
        if (!combl.empty()) {combl += "\n";}
        combl += linea;
    }

    if (!combl.empty()) {movies.push_back(asignar(combl));}

    file.close();
    return movies;
}

void Buscador::loadCSV(const string& path) {
    movies = readCSV(path);
    for (const auto& movie : movies) {
        movieMap[movie.imdb_id] = movie;
        titleTrie.insert(movie.title, movie);
        tagTrie.insert(movie.tags, movie);
        plotTrie.insert(movie.plot_synopsis, movie);
    }
}

vector<Movie> Buscador::buscar(const string& query) {
    string lowerQuery = query;
    transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);

    vector<future<vector<Movie>>> futures;

    for (const auto& strategy : strategies) {
        if (dynamic_cast<PorTitulo*>(strategy.get())) {
            futures.push_back(async([this, lowerQuery]() { return titleTrie.search(lowerQuery); }));
        } else if (dynamic_cast<PorTag*>(strategy.get())) {
            futures.push_back(async([this, lowerQuery]() { return tagTrie.search(lowerQuery); }));
        } else if (dynamic_cast<PorPlot*>(strategy.get())) {
            futures.push_back(async([this, lowerQuery]() { return plotTrie.search(lowerQuery); }));
        }
    }

    unordered_set<string> visto;
    vector<Movie> res;

    for (auto& future : futures) {
        auto strategyResults = future.get();
        for (const auto& movie : strategyResults) {
            if (visto.find(movie.imdb_id) == visto.end()) {
                visto.insert(movie.imdb_id);
                res.push_back(movie);
            }
        }
    }

    vector<pair<int, Movie>> masRelevante;
    for (const auto& movie : res) {
        int relevance = calcularRelevancia(movie, lowerQuery);
        masRelevante.emplace_back(relevance, movie);
    }

    sort(masRelevante.begin(), masRelevante.end(), [](const pair<int, Movie>& a, const pair<int, Movie>& b) {
        return a.first > b.first;
    });

    vector<Movie> top;
    int count = 0;
    for (const auto& pair : masRelevante) {
        if (count >= 10) break;
        top.push_back(pair.second);
        ++count;
    }

    return top;
}

void Buscador::addEstrategia(unique_ptr<Estrategia> estrategia) {
    strategies.push_back(move(estrategia));
}

vector<string> splitQuery(const string& query) {
    vector<string> keywords;
    stringstream ss(query);
    string word;
    while (ss >> word) {
        keywords.push_back(word);
    }
    return keywords;
}

int Buscador::calcularRelevancia(const Movie& movie, const string& query) {
    string lowerTitle = movie.title;
    transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);

    string lowerPlot = movie.plot_synopsis;
    transform(lowerPlot.begin(), lowerPlot.end(), lowerPlot.begin(), ::tolower);

    string lowerTags = movie.tags;
    transform(lowerTags.begin(), lowerTags.end(), lowerTags.begin(), ::tolower);

    int relevance = 0;
    vector<string> keywords = splitQuery(query);

    for (const auto& keyword : keywords) {
        if (lowerTitle.find(keyword) != string::npos) {
            relevance += 20;
        }
        if (lowerPlot.find(keyword) != string::npos) {
            relevance += 10;
        }
        if (lowerTags.find(keyword) != string::npos) {
            relevance += 10;
        }
    }

    return relevance;
}


vector<Movie> PorTitulo::search(const vector<Movie>& movies, const string& query) {
    vector<Movie> res;
    for (const auto& movie : movies) {
        string lowercaseTitle = movie.title;
        transform(lowercaseTitle.begin(), lowercaseTitle.end(), lowercaseTitle.begin(), ::tolower);
        if (lowercaseTitle.find(query) != string::npos) {
            res.push_back(movie);
        }
    }
    return res;
}

vector<Movie> PorTag::search(const vector<Movie>& movies, const string& query) {
    vector<Movie> res;
    for (const auto& movie : movies) {
        string lowercaseTags = movie.tags;
        transform(lowercaseTags.begin(), lowercaseTags.end(), lowercaseTags.begin(), ::tolower);
        if (lowercaseTags.find(query) != string::npos) {
            res.push_back(movie);
        }
    }
    return res;
}

vector<Movie> PorPlot::search(const vector<Movie>& movies, const string& query) {
    vector<Movie> res;
    for (const auto& movie : movies) {
        string lowercasePlot = movie.plot_synopsis;
        transform(lowercasePlot.begin(), lowercasePlot.end(), lowercasePlot.begin(), ::tolower);
        if (lowercasePlot.find(query) != string::npos) {
            res.push_back(movie);
        }
    }
    return res;
}
