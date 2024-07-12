#include "cleanData.h"
vector<CMovie>loadCsv(const string& nombreFile){
    ifstream file(nombreFile);
    vector<CMovie>movies;
    string line;
    getline(file,line);
    while (getline(file,line)){
        stringstream ss(line);
        string c;
        CMovie movi;
        bool dentroQuotes = false;
        string field;
        int fieldIndex=0;
        while (getline(ss,c,',')){
            if (c.front() == '"' && !dentroQuotes){
                dentroQuotes= true;
                field+=c.substr(1);
            } else if (c.back()=='"' && dentroQuotes){
                dentroQuotes = false;
                field+=','+c.substr(0,c.size()-1);
                switch (fieldIndex) {
                    case 2: movi.plot_synopsis=field;
                        break;
                    case 3: movi.tags=field;
                        break;
                    default: break;
                } field.clear();
                fieldIndex++;
            } else if(dentroQuotes) field+=','+c;
            else{
                switch (fieldIndex) {
                    case 0: movi.imdb_id=c;
                        break;
                    case 1: movi.title=c;
                    case 4: movi.split=c;
                    case 5: movi.synopsis_source=c;
                    default: break;
                } fieldIndex++;
            }
        }
        if (!field.empty()){
            if (fieldIndex==2)movi.plot_synopsis=field;
            else if(fieldIndex==3)movi.tags=field;
        }
        movies.push_back(movi);
    }
    return movies;
}