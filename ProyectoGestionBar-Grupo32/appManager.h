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

private:

    void MenuAdmin();       //ok
    void MenuUser();        //ok
    void Venta();           //ok
    void Historial();
    void Config();          //ok
    ///submenu:
    void AltaProd();
    void BajaProd();
    void ModStock();
    void ModPrecio();
    void GenerarBackup();
    void CargarBackup();

    void Reportes();
    void TablaPrecios();    //ok
};


