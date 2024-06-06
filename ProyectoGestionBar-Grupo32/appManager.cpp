#include "appManager.h"
#include <cstring>
#include "Terminal.h"

/*************** clase usuario provisoria ***************************/
bool User::verifyUser(std::string user, std::string pass){
    _nivelUser = 0;

    if(user == MasterUser && pass == MasterPass) _nivelUser = 1;
    if(user == userNormal && pass == passNormal) _nivelUser = 2;

    return _nivelUser;
}
/*************** clase usuario provisoria ***************************/

void AppManager::login(){
    std::string user, pass;
    Terminal terminal;
    int posx = 50;
    int posy = 13;

    rlutil::cls();
    terminal.dibujarRectangulo(2,0,30,116);
    terminal.dibujarRectangulo(41,9,11,36);

    terminal.mostrarTexto("Inicio de sesion: ",posx,posy);
    terminal.mostrarTexto("-------------------",posx,posy+1);
    terminal.mostrarTexto("Legajo: ",posx,posy+2);
    terminal.mostrarTexto("Password: ",posx,posy+3);

    while(true){
        terminal.pintarHorizontal(posx+10,16,posy+2);
        terminal.pintarHorizontal(posx+10,16,posy+3);

        user = terminal.ingresarTexto(posx + 10,posy + 2,true);
        pass = terminal.ingresarTexto(posx + 10,posy + 3,true);
        rlutil::hidecursor();

        if(usuario.verifyUser(user,pass)) break;
        else{
            rlutil::setBackgroundColor(rlutil::COLOR::RED);
            terminal.mostrarTexto("Datos incorrectos...",posx,posy+5);
            rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        }

    }

    terminal.pintarHorizontal(posx,20,posy+5);
    terminal.mostrarTexto("Ingresando",posx+5,posy +10);
    terminal.barraEspera(80,posx,posy+12);

    switch(usuario.getNivelUser()){
    case 1:
        MenuAdmin();
        break;
    case 2:
        MenuUser();
        break;
    default:
        exit(100);
        break;
    }

    rlutil::cls();
    exit(0);

}

void AppManager::MenuUser(){
    Terminal terminal;
    int opc = 0;
    int x = 4;
    int y = 5;

    terminal.pintarRectangulo(40,9,18,40);
    terminal.dibujarRectangulo(2,0,30,30);
    TablaPrecios();                     //provisoria

    do{

        terminal.crearBoton("REGISTRAR VENTA",x,y,opc == 0);
        terminal.crearBoton("HISTORIAL DE VENTAS",x,y+3,opc == 1);
        terminal.crearBoton("CERRAR SESION",x,y+6,opc == 2);
        terminal.crearBoton("SALIR",x,y+9,opc == 3);

        switch(rlutil::getkey()){
        case 14:    ///sube
            opc--;
            if(opc < 0) opc = 3;
            break;
        case 15:    ///baja
            opc++;
            if(opc > 3) opc = 0;
            break;
        case 1:     ///enter
            if(opc == 0) Venta();
            if(opc == 1) Historial();
            if(opc == 2 )login();
            if(opc == 3 )return;

            TablaPrecios();
            break;
        }

    }while(true);
}

void AppManager::MenuAdmin(){
    Terminal terminal;
    int opc = 0;
    int x = 4;
    int y = 5;

    terminal.pintarRectangulo(40,9,18,40);
    terminal.dibujarRectangulo(2,0,30,30);
    TablaPrecios();                         //provisoria

    do{

        terminal.crearBoton("REGISTRAR VENTA",x,y,opc == 0);
        terminal.crearBoton("HISTORIAL DE VENTAS",x,y+3,opc == 1);
        terminal.crearBoton("CONFIGURACION",x,y+6,opc == 2);
        terminal.crearBoton("REPORTES",x,y+9,opc == 3);
        terminal.crearBoton("CERRAR SESION",x,y+12,opc == 4);
        terminal.crearBoton("SALIR",x,y+15,opc == 5);

        switch(rlutil::getkey()){
        case 14:    ///sube
            opc--;
            if(opc < 0) opc = 5;
            break;
        case 15:    ///baja
            opc++;
            if(opc > 5) opc = 0;
            break;
        case 1:     ///enter
            if(opc == 0) Venta();
            if(opc == 1) Historial();
            if(opc == 2) Config();
            if(opc == 3) Reportes();
            if(opc == 4) login();
            if(opc == 5) return;

            TablaPrecios();
            break;
        }

    }while(true);
}

void AppManager::Config(){
    Terminal terminal;
    int opc = 0;
    int x = 4;
    int y = 5;

    terminal.pintarRectangulo(4,2,25,26);
    terminal.pintarRectangulo(34,2,27,80);

    do{
        terminal.crearBoton("ALTA PRODUCTOS",x,y,opc == 0);
        terminal.crearBoton("BAJA PRODUCTOS",x,y+3,opc == 1);
        terminal.crearBoton("MODIFICAR STOCK",x,y+6,opc == 2);
        terminal.crearBoton("MODIFICAR PRECIO",x,y+9,opc == 3);
        terminal.crearBoton("MODIFICAR USUARIOS",x,y+12,opc == 4);
        terminal.crearBoton("COPIA DE SEGURIDAD",x,y+15,opc == 5);
        terminal.crearBoton("RESTABLECER COPIA",x,y+18,opc == 6);
        terminal.crearBoton("VOLVER",x,y+21,opc == 7);

        switch(rlutil::getkey()){
        case 14:    ///sube
            opc--;
            if(opc < 0) opc = 7;
            break;
        case 15:    ///baja
            opc++;
            if(opc > 7) opc = 0;
            break;
        case 1:     ///enter

            if(opc == 1)BajaProd();

            if(opc == 7 ){
                terminal.pintarRectangulo(4,2,27,27);
                return;
            }


            break;
        }

    }while(true);
}

void AppManager::Venta(){
    std::string producto, cantidad;
    Terminal terminal;
    int opc = 0;
    int x = 4;
    int y = 5;
    bool ingreso = false;

    terminal.pintarRectangulo(4,2,25,27);

    terminal.mostrarTexto("Legajo cajero:",x,y);
    terminal.mostrarTexto((usuario.getNivelUser() == 1 ? "ADMIN":"USUARIO"),23,y);   //legajo usuario actual

    terminal.mostrarTexto("Fecha:",x,y+2);
    terminal.mostrarTexto("01/01/1900",21,y+2);  //fecha actual

    terminal.mostrarTexto("Hora: ",x,y+4);
    terminal.mostrarTexto("10:00 PM",23,y+4);    //hora actual

    terminal.mostrarTexto("producto:",x,y+6);
    terminal.mostrarTexto("cantidad:",x,y+8);
    terminal.mostrarTexto("Precio:",x,y+10);

    while(true){

        terminal.crearBoton("AGREGAR PRODUCTO",x,y+12,opc == 0);
        terminal.crearBoton("MODIFICAR PRODUCTO",x,y+15,opc == 1);
        terminal.crearBoton("FINALIZAR VENTA",x,y+18,opc == 2);

        if(!ingreso){
            producto = terminal.ingresarTexto(x+17,y+6,true);
            cantidad = terminal.ingresarTexto(x+17,y+8,true);
            terminal.mostrarTexto("$100.5",x+20,y+10);   //precio actual
            rlutil::hidecursor();
            ingreso = true;
        }

        switch(rlutil::getkey()){
        case 14:
            opc--;
            if(opc < 0) opc = 2;
            break;
        case 15:
            opc++;
            if(opc > 2) opc = 0;
            break;
        case 1:
            if(opc == 0){
                ///guarda el prod actual
                terminal.pintarRectangulo(20,y+6,4,12);
                ingreso = false;
            }

            if(opc == 1) {
                terminal.pintarRectangulo(20,y+6,4,12);
                ingreso = false;

            }

            if(opc == 2){
                ///guardar prod actual
                terminal.pintarRectangulo(4,2,25,27);
                return;
            }
            break;
        }


    }

}

void AppManager::TablaPrecios(){
    Terminal terminal;
    char alta[2] = {(char)30,'\0'};
    char baja[2] = {(char)31,'\0'};

    int x = 38;
    int y = 4;
    int contFilas = 0;
    bool status = false;
    rlutil::COLOR indicador;

    ///--------datos simulados------
    std::string bebidas[10]={
        "Whisky","Cerveza","Vinos",
        "Espumantes","Vodka","Ron",
        "Aperitivos","Tragos",
        "Cocteles","Comida"
    };
    std::string aux = "bebida";

    int elem[10] = {3,5,4,6,4,2,7,5,8,5};
    ///-------------------------

    terminal.pintarRectangulo(x,2,0,x+37,rlutil::COLOR::LIGHTRED);

    for(int i=x; i<91; i+=26){
        terminal.crearColumna("Bebida",rlutil::COLOR::LIGHTRED,i,2,false);
        terminal.crearColumna(" %Osc",rlutil::COLOR::LIGHTRED,i+8,2,false);
        terminal.crearColumna("PreUlt",rlutil::COLOR::LIGHTRED,i+16,2,i < 90);
    }


    for(int i=0; i<10; i++){
        if(contFilas > 28) {
            x += 26;
            y = 4;
        }

        terminal.crearFila(bebidas[i],rlutil::COLOR::LIGHTCYAN,x,y);
        terminal.crearFila("-----------------------",rlutil::COLOR::WHITE,x,++y);

        for(int j=0; j<elem[i];j++){
            if(contFilas == 29) {
                x += 26;
                y = 4;
            }

            if(status) indicador = rlutil::COLOR::GREEN;
            else indicador = rlutil::COLOR::RED;

            terminal.crearFila("bebida",rlutil::COLOR::WHITE,x,++y);
            terminal.crearFila("123,5",rlutil::COLOR::WHITE,x+16,y);
            terminal.crearFila((status == true ? alta : baja),indicador,x+13,y);
            terminal.crearFila("%1,25",indicador,x+8,y);

            status = !status;
            contFilas = y;
        }

        y += 2;
        contFilas = y;
    }
}

void AppManager::Historial(){
    Terminal terminal;
    int opc = 0;
    char arriba[2] = {(char)30,'\0'};
    char abajo[2] = {(char)31,'\0'};

    terminal.pintarRectangulo(34,2,27,80);

    while(true){

        terminal.crearBotonVertical(arriba,112,8,opc == 1);
        terminal.crearBotonVertical(abajo,112,14,opc == 2);

        terminal.crearBoton("Hoy",33,1,opc == 3);
        terminal.crearBoton("Ultimos 15 dias",61,1,opc == 4);
        terminal.crearBoton("Ultimos 30 dias",89,1,opc == 5);

        switch(rlutil::getkey()){
        case 14:        //arriba
            opc = 1;
            break;
        case 15:
            opc = 2;
            break;
        case 17:
            if(opc < 3) opc = 5;
            else{
                opc++;
                if(opc > 5) opc = 5;
            }
            break;
        case 16:
            if(opc < 3) opc = 3;
            else{
                opc--;
                if(opc < 3) opc = 3;
            }
            break;
        case 0:
            terminal.pintarRectangulo(34,2,27,84);
            return;
            break;
        }
    }
}

void AppManager::AltaProd(){
    Terminal terminal;
    terminal.pintarRectangulo(34,2,27,80);
    rlutil::anykey();
}

void AppManager::BajaProd(){
    Terminal terminal;
    int x=50;
    int y=10;

    terminal.pintarRectangulo(34,2,27,80);
    terminal.crearBoton("hola",x,y,true);
    rlutil::anykey();
}

void AppManager::ModStock(){
    Terminal terminal;
    terminal.pintarRectangulo(34,2,27,80);
    rlutil::anykey();
}

void AppManager::ModPrecio(){
    Terminal terminal;
    terminal.pintarRectangulo(34,2,27,80);
    rlutil::anykey();
}

void AppManager::GenerarBackup(){
    Terminal terminal;
    terminal.pintarRectangulo(34,2,27,80);
    rlutil::anykey();
}

void AppManager::CargarBackup(){
    Terminal terminal;
    terminal.pintarRectangulo(34,2,27,80);
    rlutil::anykey();
}

void AppManager::Reportes(){
    Terminal terminal;
    terminal.pintarRectangulo(34,2,27,80);
    rlutil::anykey();;
}


