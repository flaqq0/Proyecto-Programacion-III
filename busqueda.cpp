#include "librerias.h"
#include <fstream>
#include <sstream>

struct Movie{
    string imdb_id,title,plot_synopsis,tags,split,synopsis_source;
};
vector<Movie>loadCsv(const string& filenam){
    ifstream file(filenam);
    vector<Movie> peliculas;
    string line;

    getline(file,line);
     while (getline(file,line)){
        stringstream ss(line);
        string cell;
        Movie movie;
        bool insidequotes = false;
        string field;
        int fieldIndex=0;
         while (getline(ss,cell,',')){
             if(cell.front() == '"' && !insidequotes){
                 insidequotes= true;
                 field+=cell.substr(1);
             } else if(cell.back() == '"' && insidequotes){
                 insidequotes = false;
                 field+=',' + cell.substr(0,cell.size() -1);
                 switch (fieldIndex) {
                     case 2:
                         movie.plot_synopsis=field;
                         break;
                     case 3:
                         movie.tags = field;
                         break;
                     default:
                         break;
                 }
                 field.clear();
                 fieldIndex++;
             } else if(insidequotes) field+=','+cell;
             else{
                 switch (fieldIndex) {
                     case 0:
                         movie.imdb_id=cell;
                         break;
                     case 1:
                         movie.title=cell;
                     case 4:
                         movie.split=cell;
                     case 5:
                         movie.synopsis_source=cell;
                     default:
                         break;
                 } fieldIndex++;
             }
         }
         if (!field.empty()){
             if (fieldIndex==2)movie.plot_synopsis=field;
             else if(fieldIndex==3) movie.tags=field;
         }
        peliculas.push_back(movie);
    }
    return peliculas;
}
int main(){
    string fil = "C:/Users/Usuario/Desktop/Utec/2024-1/PrograIII/PROYECTOFINAL/Proyecto-Programacion-III/peliculas.csv";
    vector<Movie>movies= loadCsv(fil);
    for (int i=0; i<1; i++){
        cout<<"ID :"<<movies[i].imdb_id<<endl;
        cout<<"TITTLE :"<<movies[i].title<<endl;
        cout<<"PLOT SYNOPSIS :"<<movies[i].plot_synopsis<<endl;
        cout<<"TAGS :"<<movies[i].tags<<endl;
        cout<<"SPLIT :"<<movies[i].split<<endl;
        cout<<"SYNOPSIS SOURCE:"<<movies[i].synopsis_source<<endl;
        cout<<"- - - - - - - - - - - - - - - - - - - - - - - -"<<endl;
    }
    /*
    for (const auto& mov:movies) {
        cout<<"ID :"<<mov.imdb_id<<endl;
        cout<<"TITTLE :"<<mov.title<<endl;
        cout<<"PLOT SYNOPSIS :"<<mov.plot_synopsis<<endl;
        cout<<"TAGS :"<<mov.tags<<endl;
        cout<<"SPLIT :"<<mov.split<<endl;
        cout<<"SYNOPSIS SOURCE:"<<mov.synopsis_source<<endl;
    }
     */
    return 0;
}