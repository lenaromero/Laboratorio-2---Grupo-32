#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

#include <iostream>
#include <string>

class Usuario {
private:
    int legajo;
    std::string contraseña;
    int categoria;
    Persona datosPersonales;
 //   bool estado;

public:

    void setLegajo(int nuevoLegajo) {legajo = nuevoLegajo;}
    void setContraseña(const std::string& nuevaContraseña) {contraseña = nuevaContraseña;}
    void setCategoria(int nuevaCategoria) {categoria = nuevaCategoria;}
    void setEstado(bool nuevoEstado) {estado = nuevoEstado;}
    Persona getDatosPersonales() const {
        return datosPersonales;
    }

//    int getLegajo() const {return legajo;}
//    const std::string& getContraseña() const {return contraseña;}
//    int getCategoria() const {return categoria;}
//    bool getEstado() const {return estado;}
    void guardarUsuario() {
        ofstream archivo("usuarios.txt", ios::app);  // Abre el archivo en modo append
        if (archivo.is_open()) {
            archivo << legajo << "," << contraseña << "," << categoria << "," << estado << "\n";
            archivo.close();
            cout << "Usuario guardado correctamente en el archivo.\n";
        } else {
            cout << "Error al abrir el archivo para guardar el usuario.\n";
        }
    }
    void Usuario::guardarEnArchivo() {
    string rutaArchivo = "data/usuarios.txt";
    ofstream archivo(rutaArchivo, ios::app);
    if (archivo.is_open()) {
        archivo << datosPersonales.getNombre() << "," << datosPersonales.getApellido() << ","
                << datosPersonales.getDiaNacimiento() << "," << datosPersonales.getMesNacimiento() << ","
                << datosPersonales.getAnioNacimiento() << "," << legajo << "," << contraseña << "\n";
        archivo.close();
        return{0};
    } else {
        return {99};
    }
}
};

#endif // USUARIO_H_INCLUDED
