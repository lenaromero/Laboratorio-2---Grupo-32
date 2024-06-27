<<<<<<< HEAD
#ifndef PARCIAL1L_H_INCLUDED
#define PARCIAL1L_H_INCLUDED

class Persona{
private:
    const std::string nombre;
    const std::string apellido;
=======
#include <iostream>
#ifndef PARCIAL1L_H_INCLUDED
#define PARCIAL1L_H_INCLUDED

void cargarCadena(char *pal, int tam){
    int i;
    fflush(stdin);
    for(i=0; i<tam; i++)
    {
        pal[i]=cin.get();
        if(pal[i]=='\n') break;
    }
    pal[i]='\0';
    fflush(stdin);
}

class Fecha{
private:
    int dia,mes, anio;
public:
    void Cargar(){
        cin>>dia;
        cin>>mes;
        cin>>anio;
    }
    void Mostrar(){
        cout<<dia<<"/";
        cout<<mes<<"/";
        cout<<anio<<endl;
    }
    int getDia(){return dia;}
    int getMes(){return mes;}
    int getAnio(){return anio;}

    void setDia(int d){dia=d;}
    void setMes(int m){mes=m;}
    void setAnio(int a){anio=a;}

};


class Persona{
private:
    char nombre[30];
    char apellido[30];
>>>>>>> e8df7e2830989838d9caa4a48fa65ed64cde6d32
    Fecha fecha_nacimiento;
    Fecha fecha_ingreso;
public:
    void Cargar(){
<<<<<<< HEAD
        std::cout << "Nombre: ";
        std::getline(std::cin, nombre);
        std::cout << "Apellido: ";
        std::getline(std::cin, apellidop);
=======
        cargarCadena(nombre,29);
        cargarCadena(apellido,29);
>>>>>>> e8df7e2830989838d9caa4a48fa65ed64cde6d32
        Fecha fecha_nacimiento;
        Fecha fecha_ingreso;
    }

<<<<<<< HEAD
    std::string getNombre() const {
        return nombre;
    }
    std::string getApellido() const {
        return apellido;
    }
=======
    const char *getNombre(){return nombre;}
    const char *getApellido(){return apellido;}
>>>>>>> e8df7e2830989838d9caa4a48fa65ed64cde6d32
    Fecha getFechaNacimiento(){return fecha_nacimiento;}
    Fecha getFechaIngreso(){return fecha_ingreso;}

    void Mostrar(){
<<<<<<< HEAD
        std::cout << "Nombre: " << nombre << ", Apellido: " << apellido << endl;
    }
};
<<<<<<< HEAD:Funciones/classPersona.h
#endif // USUARIO_H_INCLUDED
=======
>>>>>>> e8df7e2830989838d9caa4a48fa65ed64cde6d32:ProyectoGestionBar-Grupo32/classPersona.h
=======
        cout<<nombre<<endl;
        cout<<apellido<<endl;
        fecha_nacimiento.Mostrar;
        fecha_ingreso.Mostrar;
    }
};
<<<<<<<< HEAD:Funciones/classPersona.h

class Usuario{
private:
    int legajo;
    char contrasenia[10];
    int categoria;
    bool estado;
public:
    void Cargar(){
        cin>>legajo;
        cargarCadena(contrasenia,10);
        cin>>categoria;
        estado=true;
    }
    
    void Mostrar(){
        cout<<legajo<<endl;
        cout<<contraseña<<endl;
        cout<<categoria<<endl;
        cout<<estado<<endl;
    } 

// GET
    int getLegajo(){return legajo;}
    const char *getContrasenia(){return nombre;}
    int getCategoria(){return categoria;}
    bool getEstado(){return estado;}

// SET
    void setLegajo(int l){legajo=l;}
    void setContrasenia(const char *c){strcpy(contrasenia, c);}
    void setCategoria(int c){categoria=c}
    void setEstado(bool e){estado=e;}


};
========
>>>>>>>> e8df7e2830989838d9caa4a48fa65ed64cde6d32:ProyectoGestionBar-Grupo32/classPersona.h
>>>>>>> e8df7e2830989838d9caa4a48fa65ed64cde6d32
