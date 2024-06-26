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
#endif // USUARIO_H_INCLUDED
