#pragma once
#include <iostream>


/*************** clase usuario provisoria ***************************/
class User{

private:
    /// provicional a modo prueba
    std::string MasterUser = "admin";
    std::string MasterPass = "admin";

    std::string userNormal = "user";
    std::string passNormal = "pass";
    int _nivelUser;

public:
    bool verifyUser(std::string user, std::string pass);
    int getNivelUser(){return _nivelUser;}
};
/*************** clase usuario provisoria ***************************/

class AppManager{

public:

    User usuario;
    void login();
    float strToInt(std::string);

private:

    void MenuAdmin();       //ok
    void MenuUser();        //ok
    void Venta();           //ok
    void Historial();           //a medias

    /************************************************/
    void Config();              //ok

    ///submenus:
    /// - productos:
    void MenuProductos();       //ok
    void MostrarProductos();   //a medias
    void AltaProd();           //ok
    bool IngresoProdBebida();  //OK
    bool IngresoProdComida();  //OK
    void BajaProd();            //OK
    void ModStock();            //OK
    void ModPrecio();           //OK
    /// - usuarios:
    void MenuUsarios();         //OK
    void MostrarUsuarios();
    void AltaUsuario();         //OK
    void BajaUsuario();
    /// - copia de seguridad
    void MenuCopiaSeg();        //OK
    void GenerarBackup();
    void CargarBackup();
    /************************************************/


    void Reportes();
    void TablaPrecios();    //ok


};


