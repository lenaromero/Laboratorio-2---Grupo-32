#ifndef PARCIAL1L_H_INCLUDED
#define PARCIAL1L_H_INCLUDED

class ArchivoUsuarios{
private:
    char nombre[30];
public:
    ArchivoUsuarios(const char *n){
        strcpy(nombre, n);
    }
    Usuario leerRegistro(int pos){
        Usuario reg;
        reg.setEstado(false);
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return reg;
        fseek(p, sizeof reg*pos,0);
        fread(&reg, sizeof reg,1, p);
        fclose(p);
        return reg;
    }
    int contarRegistros(){
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return -1;
        fseek(p, 0,2);
        int tam=ftell(p);
        fclose(p);
        return tam/sizeof(Usuario);
    }
    bool grabarRegistro(Usuario reg){
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        int escribio=fwrite(&reg, sizeof reg,1, p);
        fclose(p);
        return escribio;
    }
};

int obtenerUltimoLegajo() {
    ifstream archivo("usuarios.txt");
    int ultimoLegajo = 0;
    string linea;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string token;
            getline(ss, token, ',');  // Obtener primer token (nombre)
            int legajoActual;
            ss >> legajoActual;
            if (legajoActual > ultimoLegajo) {
                ultimoLegajo = legajoActual;
            }
        }
        archivo.close();
    }

    return ultimoLegajo;
}

void altaUsuario() {
    string nombre, apellido, contraseña;
    int diaNac, mesNac, anioNac;

    Persona datosPersonales(nombre, apellido, diaNac, mesNac, anioNac);

    string contraseñaTemporal;
    contraseña;
    cin.ignore();
    getline(contraseñaTemporal);
    if (contraseñaTemporal.size() != 8 || !isdigit(contraseñaTemporal)) {
        cout << "La contraseña debe ser numérica y tener exactamente 8 dígitos.\n";
        return;
    }

    int nuevoLegajo = ultimoLegajo + 1;

    // Crear un objeto Usuario con los datos proporcionados
    Usuario nuevoUsuario(nuevoLegajo, contraseña, datosPersonales);

    // Guardar el usuario en el archivo
    nuevoUsuario.guardarEnArchivo();
}

#endif // USUARIO_H_INCLUDED
