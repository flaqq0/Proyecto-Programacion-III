#include "Usuario.h"

Usuario::Usuario() {}

Usuario::Usuario(string nombre, string email, string password, Planes *plan) : nombre(nombre),
email(email), password(password), plan(plan) {}

const string &Usuario::getNombre() const {return nombre;}
void Usuario::setNombre(const string &nombre) {Usuario::nombre = nombre;}
const string &Usuario::getEmail() const {return email;}
void Usuario::setEmail(const string &email) {Usuario::email = email;}
const string &Usuario::getPassword() const {return password;}
void Usuario::setPassword(const string &password) {Usuario::password = password;}
Planes *Usuario::getPlan() const {return plan;}
void Usuario::setPlan(Planes *plan) {Usuario::plan = plan;}

bool Usuario::verificarNombre(const string &name) {
    bool verify= name.size()>=2;
    if (!verify) cout<<"* El nombre debe tener mas de 1 caracter!"<<endl;
    return verify;
}
bool Usuario::verificarCorreo(const string &correo) {
    bool verify = correo.find('@') != string::npos;
    if (!verify) cout << "* Correo invalido!" << endl;
    return verify;
}
bool Usuario::verificarContra(const string &contra) {
    bool verify = (contra.size() > 7 && contra.size() < 61);
    if (!verify) cout << "* La contrasena debe tener entre 8 a 60 caracteres!" << endl;
    return verify;
}
Usuario::~Usuario() {
    delete plan;
    plan= nullptr;
}