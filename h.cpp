#include "librerias.h"
class Plan{
protected:
    double precio;
    string name, quality, resolution;
    bool spatialAudio;
    int devicesSameTime, downloadDevices;


public:
    Plan(string name, double price, string qual, string resol, bool spatialAud, int devicesametime, int download):
    name(name),precio(price), quality(qual), resolution(resol), spatialAudio(spatialAud),
    devicesSameTime(devicesametime), downloadDevices(download){}

    virtual ~Plan(){}
    string getName()const{return name;}
    double getPrecio()const{return precio;}
    string getQuality()const{return quality;}
    string getResolution()const{return resolution;}
    bool getSpatialAudio()const{return spatialAudio;}
    int getDevicesSameTime()const{return devicesSameTime;}
    int getDownloadDevices()const{return downloadDevices;}

};
struct Premium : virtual public Plan{
    Premium() : Plan("Premium",44.90,"Best","4k",true,4,6){}
};
struct Standard : virtual public Plan{
    Standard() : Plan("Standard",34.90,"Great","1080p",false,2,2){}
};
struct Basic : virtual public Plan{
    Basic() : Plan("Basic",24.90,"Good","720p", false,1,1){}
};

class Usuario{
    string nombre, email, password;
    Plan *plan;
public:
    Usuario() {}
    Usuario(string nombre, string mail, string pass, Plan* p){
        this->nombre=std::move(nombre);
        this->email = std::move(mail);
        this->password = std::move(pass);
        this->plan=p;
    }
    ~Usuario(){delete plan;plan= nullptr;}
    string getNombre()const{return nombre;}
    string getMail()const{return email;}
    string getPass()const{return password;}
    string setNombre()const{return nombre;}
    const Plan& getPlan()const{return *plan;}
    void setPlan(Plan *p) {Usuario::plan = p;}
};
bool verificarNombre(const string &nombre){
    bool verify= nombre.size()>=2;
    if (!verify) cout<<"* El nombre debe tener mas de 1 caracter!"<<endl;
    return verify;
}
bool verificarCorreo(const string& correo) {
    bool verify = correo.find('@') != string::npos;
    if (!verify) cout << "* Correo invalido!" << endl;
    return verify;
}
bool verificarContra(const string& contra) {
    bool verify = (contra.size() > 7 && contra.size() < 61);
    if (!verify) cout << "* La contrasena debe tener entre 8 a 60 caracteres!" << endl;
    return verify;
}

void FAKEpaysimulation(Plan plan){
    string numTarjeta, fecha;
    cout<<"\n- - - - - - - - - - - - - - - - - - - - - -\n|                                         |"<<endl;
    cout<<"|               PASO 3 de 3               |\n|         Configura tu tarjeta de         |\n|            credito o debito             |"<<endl;
    cout<<"|  VISA - CMR - Am.Express - Dinners Club |\n|                                         |"<<endl;
    if (plan.getName()=="Basic") cout<<"| "<<plan.getPrecio()<<"0 PEN al mes                ("<<plan.getName()<<") |"<<endl;
    else if(plan.getName()=="Standard") cout<<"| "<<plan.getPrecio()<<"0 PEN al mes             ("<<plan.getName()<<") |"<<endl;
    else cout<<"| "<<plan.getPrecio()<<"0 PEN al mes              ("<<plan.getName()<<") |"<<endl;
    cout<<"| Numero de tarjeta :",cin>>numTarjeta;
    cout<<"| Fecha de vencimiento :",cin>>fecha;
    cout<<"|                                         |\n- - - - - - - - - - - - - - - - - - - - - -"<<endl;
}
void selectPlan(Usuario *user){
    string c;
    bool g;
    do {
        cout<<"| Ingrese el plan que desea comprar       |\n| ej. PREMIUM - Premium - premium - p     |\n| >>";
        cin>>c;
        cout<<"|                                         |"<<endl;
        transform(c.begin(), c.end(), c.begin(), [](unsigned char c) { return toupper(c); });
        if (c =="PREMIUM"||c=="P"){g= true;
            cout<<"- - - - - - - - - - - - - - - - - - - - - -"<<endl;
            Plan* premium = new Premium();
            FAKEpaysimulation(*premium);
            user->setPlan(premium);
        }else if(c=="STANDARD"||c=="ESTANDAR"||c=="S"||c=="E"){g= true;
            cout<<"- - - - - - - - - - - - - - - - - - - - - -"<<endl;
            Plan* standard = new Standard();
            FAKEpaysimulation(*standard);
            user->setPlan(standard);
        }else if(c=="BASICO"||c=="BASIC"||c=="B"){g= true;
            cout<<"- - - - - - - - - - - - - - - - - - - - - -"<<endl;
            Plan* basic = new Basic();
            FAKEpaysimulation(*basic);
            user->setPlan(basic);
        } else{g= false;
            cout<<"| * Error. Plan no encontrado!            |\n|                                         |"<<endl;
        }
    } while (!g);
}
void imprimirPlanes(const vector<Plan*>&planes){
    for(int i=0; i<planes.size(); i++){
        if (i==0){cout<<"|  *  *  *  *  *  PREMIUM  *  *  *  *  *  |"<<endl;}
        else if(i==1){cout<<"|  *  *  *  *  *  STANDART *  *  *  *  *  |"<<endl;}
        else{cout<<"|  *  *  *  *  *   BASICO  *  *  *  *  *  |"<<endl;}
        cout<<"| Precio mensual                 S/ "<<planes[i]->getPrecio()<<"  |"<<endl;
        if (i==1){
            cout<<"| Calidad de audio y video         "<<planes[i]->getQuality()<<"  |"<<endl;
            cout<<"| Resolucion                       "<<planes[i]->getResolution()<<"  |"<<endl;
        }
        else{
            cout<<"| Calidad de audio y video          "<<planes[i]->getQuality()<<"  |"<<endl;
            if (i==0){cout<<"| Resolucion                          "<<planes[i]->getResolution()<<"  |"<<endl;}
            if (i==2) cout<<"| Resolucion                        "<<planes[i]->getResolution()<<"  |"<<endl;
        }
        if (planes[i]->getSpatialAudio()) cout<<"| Audio Espacial                Incluido  |"<<endl;
        cout<<"| Dispositivos Netflix a la vez        "<<planes[i]->getDevicesSameTime()<<"  |"<<endl;
        cout<<"| Descargas en dispositivos            "<<planes[i]->getDownloadDevices()<<"  |"<<endl;
        cout<<"|_________________________________________|"<<endl;
        if(i!=2){cout<<"|                                         |"<<endl;}
    }
}
Usuario Registrar(){
    string nombre, email, contra;
    cout<<"\n- - - - - - - - - - - - - - - - - - - - - -\n"
          "|                                         |"<<endl;
    cout<<"|               PASO 1 de 3               |"<<endl;
    cout<<"| Ingrese su nombre para crear una cuenta |"<<endl;
    do {
        cout<<"| >>", cin>>nombre;
    } while (!verificarNombre(nombre));
    cout<<"| Ingrese su email                        |"<<endl;
    do {
        cout<<"| >>", cin>>email;
    } while (!verificarCorreo(email));
    cout<<"|  Ingrese su contrasena                  |"<<endl;
    do {
        cout<<"| >>", cin>>contra;
    } while (!verificarContra(contra));
    cout<<"|                                         |\n- - - - - - - - - - - - - - - - - - - - - -"<<endl;
    cout<<"|                                         |"<<endl;
    cout<<"|               PASO 2 de 3               |"<<endl;
    cout<<"|                                         |"<<endl;
    vector<Plan*> planes = { new Premium(), new Standard(), new Basic() };
    imprimirPlanes(planes);
    cout<<"|                                         |"<<endl;
    Usuario usuario(nombre,email, contra, nullptr);
    selectPlan(&usuario);
    return usuario;
}
void IniciarSesion(vector<Usuario>&users){
    string mail;
    bool check1= false,check2= false;
    cout<<"\n- - - - - - - - - - - - - - - - - - - - - -"<<endl;
    cout<<"|                                         |"<<endl;
    cout<<"|             Iniciar Sesion              |"<<endl;
    cout<<"| Ingrese su Email                        |\n| >>";
    do {
        cin>>mail;
        for(const auto & user : users)
            if(user.getMail()==mail) check1= true;
        if (!check1) cout<<"| Por favor ingrese un correo valido      |\n| >>";
    } while (!check1);
    string contra;
    cout<<"| Ingrese su contrasena                   |\n| >>";
    do {
        cin>>contra;
        for (const auto &user:users)
            if(user.getPass()==contra)check2= true;
        if(!check2)cout<<"| Ingrese una contrasena valida           |\n| >>";
    } while (!check2);
    cout<<"MOSTRAR COSO DE NETFLIX"<<endl;
}
void opcionMenu(double op, vector<Usuario>& usuarios) {
    if (op == 1){
        cout<<"- - - - - - - - - - - - - - - - - - - - - -"<<endl;
        Usuario nuevouser=Registrar();
        usuarios.push_back(nuevouser);
        cout<<"- - - - - - - - - - - - - - - - - - - - - -"<<endl;
        cout<<"|> Usuari@ "<<nuevouser.getNombre()<<" registrado con exito"<<endl;
        cout<<"- - - - - - - - - - - - - - - - - - - - - -"<<endl;
        IniciarSesion(usuarios);
    }
    else if (op == 2){
        cout<<"- - - - - - - - - - - - - - - - - - - - - -"<<endl;
        IniciarSesion(usuarios);
    }
    else{
        cout<<"|             Opcion invalida             |"<<endl;
        cout<<"| >>";
    }
}
void menuInicio(vector<Usuario>&usuarios){
    double opc;
    cout<<"- - - - - - - - - NETFLIX - - - - - - - - -"<<endl;
    cout<<"|                                         |"<<endl;
    cout<<"|            1. Registrarse               |"<<endl;
    cout<<"|            2. Iniciar sesion            |"<<endl;
    cout<<"|                                         |"<<endl;
    cout<<"| >>";
    do {
        cin>>opc;
        opcionMenu(opc,usuarios);
    } while (opc !=1 && opc !=2);
}