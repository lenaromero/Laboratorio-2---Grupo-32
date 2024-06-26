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
    Fecha fecha_nacimiento;
    Fecha fecha_ingreso;
public:
    void Cargar(){
        cargarCadena(nombre,29);
        cargarCadena(apellido,29);
        Fecha fecha_nacimiento;
        Fecha fecha_ingreso;
    }

    const char *getNombre(){return nombre;}
    const char *getApellido(){return apellido;}
    Fecha getFechaNacimiento(){return fecha_nacimiento;}
    Fecha getFechaIngreso(){return fecha_ingreso;}

    void Mostrar(){
        cout<<nombre<<endl;
        cout<<apellido<<endl;
        fecha_nacimiento.Mostrar;
        fecha_ingreso.Mostrar;
    }
};

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