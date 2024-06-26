#ifndef PARCIAL1L_H_INCLUDED
#define PARCIAL1L_H_INCLUDED

class Persona{
private:
    const std::string nombre;
    const std::string apellido;
    Fecha fecha_nacimiento;
    Fecha fecha_ingreso;
public:
    void Cargar(){
        std::cout << "Nombre: ";
        std::getline(std::cin, nombre);
        std::cout << "Apellido: ";
        std::getline(std::cin, apellidop);
        Fecha fecha_nacimiento;
        Fecha fecha_ingreso;
    }

    std::string getNombre() const {
        return nombre;
    }
    std::string getApellido() const {
        return apellido;
    }
    Fecha getFechaNacimiento(){return fecha_nacimiento;}
    Fecha getFechaIngreso(){return fecha_ingreso;}

    void Mostrar(){
        std::cout << "Nombre: " << nombre << ", Apellido: " << apellido << endl;
    }
};
<<<<<<< HEAD:Funciones/classPersona.h
#endif // USUARIO_H_INCLUDED
=======
>>>>>>> e8df7e2830989838d9caa4a48fa65ed64cde6d32:ProyectoGestionBar-Grupo32/classPersona.h
