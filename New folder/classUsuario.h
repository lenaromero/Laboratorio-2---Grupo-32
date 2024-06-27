#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

#include <iostream>
#include <string>

class Usuario {
private:
    int legajo;
    std::string contraseña;
    int categoria;
    bool estado;

public:

    void setLegajo(int nuevoLegajo) {legajo = nuevoLegajo;}
    void setContraseña(const std::string& nuevaContraseña) {contraseña = nuevaContraseña;}
    void setCategoria(int nuevaCategoria) {categoria = nuevaCategoria;}
    void setEstado(bool nuevoEstado) {estado = nuevoEstado;}

//    int getLegajo() const {return legajo;}
//    const std::string& getContraseña() const {return contraseña;}
//    int getCategoria() const {return categoria;}
//    bool getEstado() const {return estado;}
};

#endif // USUARIO_H_INCLUDED
