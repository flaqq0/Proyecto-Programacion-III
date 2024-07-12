#ifndef PROYECTOLIMPIO_USUARIO_H
#define PROYECTOLIMPIO_USUARIO_H
#include "Planes.h"
class Usuario {
    string nombre, email, password;
    Planes *plan;
public:
    Usuario();
    Usuario(string nombre, string email, string password, Planes *plan);

    const string &getNombre() const;
    void setNombre(const string &nombre);

    const string &getEmail() const;
    void setEmail(const string &email);

    const string &getPassword() const;
    void setPassword(const string &password);

    Planes *getPlan() const;
    void setPlan(Planes *plan);

    bool verificarNombre(const string &name);
    bool verificarCorreo(const string &correo);
    bool verificarContra(const string &contra);
    virtual ~Usuario();
};


#endif
