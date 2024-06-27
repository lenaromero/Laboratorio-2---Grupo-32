#include "appManager.h"
#include "Terminal.h"
#include "menuOptions.h"
#include "cuadro.h"
#include <cstring>
#include <cmath>

/*************** clase usuario provisoria ***************************/
bool User::verifyUser(std::string user, std::string pass){
    _nivelUser = 0;

    if(user == MasterUser && pass == MasterPass) _nivelUser = 1;
    if(user == userNormal && pass == passNormal) _nivelUser = 2;

    return _nivelUser;
}
/*************** clase usuario provisoria ***************************/

float AppManager::strToInt(std::string numero){
    char* aux;
    float nuevoNum = 0;
    bool flag = false;
    int contDec = 0;

    aux = new char[strlen(numero.c_str())];
    strcpy(aux,numero.c_str());

    for(int i=0; i<strlen(numero.c_str()); i++){

        if(aux[i] < 48 || aux[i] > 57){

            if(aux[i] == 46){
                flag = true;
                continue;
            }
            else return -1;
        }

        if(flag)contDec++;
        nuevoNum *= 10;
        nuevoNum += static_cast<float>(aux[i]) - 48;
    }

    if(flag) nuevoNum /= pow(10,contDec);

    return nuevoNum;
}

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
    terminal.barraEspera(80,posx-8,posy+12);

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

void AppManager::MenuAdmin(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION1;
    int x = 4;
    int y = 5;

    terminal.pintarRectangulo(40,9,18,40);
    terminal.dibujarRectangulo(2,0,30,30);
    TablaPrecios();

    do{

        terminal.crearBoton("REGISTRAR VENTA",x,y,SELECT == OPC::OPCION1);
        terminal.crearBoton("HISTORIAL DE VENTAS",x,y+3,SELECT == OPC::OPCION2);
        terminal.crearBoton("CONFIGURACION",x,y+6,SELECT == OPC::OPCION3);
        terminal.crearBoton("REPORTES",x,y+9,SELECT == OPC::OPCION4);
        terminal.crearBoton("CERRAR SESION",x,y+12,SELECT == OPC::OPCION5);
        terminal.crearBoton("SALIR",x,y+15,SELECT == OPC::OPCION6);

        switch(rlutil::getkey()){
        case 14:    ///sube
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION6;
            else MenuOption::anteriorOpcion(SELECT);

            break;
        case 15:    ///baja
            if(SELECT == OPC::OPCION6) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);

            break;
        case 1:     ///enter
            if(SELECT == OPC::OPCION1) Venta();
            if(SELECT == OPC::OPCION2) Historial();
            if(SELECT == OPC::OPCION3) Config();
            if(SELECT == OPC::OPCION4) Reportes();
            if(SELECT == OPC::OPCION5) login();
            if(SELECT == OPC::OPCION6) return;

            TablaPrecios();
            break;
        }

    }while(true);
}

void AppManager::MenuUser(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION1;
    int x = 4;
    int y = 5;

    terminal.pintarRectangulo(40,9,18,40);
    terminal.dibujarRectangulo(2,0,30,30);
    TablaPrecios();

    do{

        terminal.crearBoton("REGISTRAR VENTA",x,y,SELECT == OPC::OPCION1);
        terminal.crearBoton("HISTORIAL DE VENTAS",x,y+3,SELECT == OPC::OPCION2);
        terminal.crearBoton("CERRAR SESION",x,y+6,SELECT == OPC::OPCION3);
        terminal.crearBoton("SALIR",x,y+9,SELECT == OPC::OPCION4);

        switch(rlutil::getkey()){
        case 14:    ///sube
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION4;
            else MenuOption::anteriorOpcion(SELECT);

            break;
        case 15:    ///baja
            if(SELECT == OPC::OPCION4) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);

            break;
        case 1:     ///enter
            if(SELECT == OPC::OPCION1) Venta();
            if(SELECT == OPC::OPCION2) Historial();
            if(SELECT == OPC::OPCION3) login();
            if(SELECT == OPC::OPCION4) return;

            TablaPrecios();
            break;
        }

    }while(true);
}

void AppManager::Venta(){
    std::string producto, cantidad;
    Terminal terminal;
    OPC SELECT = OPC::OPCION_NULL;
    int x = 4;
    int y = 5;
    bool ingreso = false;

    terminal.pintarRectangulo(4,2,25,27);

    terminal.mostrarTexto("Legajo cajero:",x,y);
    terminal.mostrarTexto((usuario.getNivelUser() == 1 ? "ADMIN":"USUARIO"),23,y);   /// legajo usuario actual
    terminal.mostrarTexto("Fecha:",x,y+2);
    terminal.mostrarTexto("01/01/1900",21,y+2);  /// fecha actual
    terminal.mostrarTexto("Hora: ",x,y+4);
    terminal.mostrarTexto("10:00 PM",23,y+4);    /// hora actual
    terminal.mostrarTexto("producto:",x,y+6);
    terminal.mostrarTexto("cantidad:",x,y+8);
    terminal.mostrarTexto("Precio:",x,y+10);

    terminal.crearBoton("AGREGAR PRODUCTO",x,y+12,SELECT == OPC::OPCION1);
    terminal.crearBoton("MODIFICAR PRODUCTO",x,y+15,SELECT == OPC::OPCION2);
    terminal.crearBoton("FINALIZAR VENTA",x,y+18,SELECT == OPC::OPCION3);

    while(true){

        if(!ingreso){
            producto = terminal.ingresarTexto(x+17,y+6,true);
            cantidad = terminal.ingresarTexto(x+17,y+8,true);
            terminal.mostrarTexto("$100.5",x+20,y+10);   //precio actual
            rlutil::hidecursor();
            ingreso = true;
            SELECT = OPC::OPCION1;
        }

        terminal.crearBoton("AGREGAR PRODUCTO",x,y+12,SELECT == OPC::OPCION1);
        terminal.crearBoton("MODIFICAR PRODUCTO",x,y+15,SELECT == OPC::OPCION2);
        terminal.crearBoton("FINALIZAR VENTA",x,y+18,SELECT == OPC::OPCION3);

        switch(rlutil::getkey()){
        case 14:
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION3;
            else MenuOption::anteriorOpcion(SELECT);

            break;
        case 15:
            if(SELECT == OPC::OPCION3) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);

            break;
        case 1:
            if(SELECT == OPC::OPCION3){
                ///guardar prod actual
                terminal.pintarRectangulo(4,2,25,27);
                return;
            }
            terminal.pintarRectangulo(20,y+6,4,12);

            if(SELECT == OPC::OPCION1){
                ///guarda el prod actual
                ingreso = false;
            }

            if(SELECT == OPC::OPCION2) ingreso = false;

            break;
        }
    }
}

void AppManager::Historial(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION1;
    char arriba[2] = {(char)30,'\0'};
    char abajo[2] = {(char)31,'\0'};

    terminal.pintarRectangulo(34,2,27,82);

    while(true){

        terminal.crearBotonVertical(arriba,112,8,SELECT == OPC::OPCION1);
        terminal.crearBotonVertical(abajo,112,14,SELECT == OPC::OPCION2);

        terminal.crearBoton("Hoy",33,1,SELECT == OPC::OPCION3);
        terminal.crearBoton("Ultimos 15 dias",61,1,SELECT == OPC::OPCION4);
        terminal.crearBoton("Ultimos 30 dias",89,1,SELECT == OPC::OPCION5);

        switch(rlutil::getkey()){
        case 14:        //arriba
            SELECT = OPC::OPCION1;
            break;
        case 15:
            SELECT = OPC::OPCION2;
            break;
        case 17:
            if(SELECT < OPC::OPCION3) SELECT = OPC::OPCION5;
            else{
                MenuOption::siguienteOpcion(SELECT);
                if(SELECT > OPC::OPCION5) SELECT = OPC::OPCION5;
            }
            break;
        case 16:
            if(SELECT < OPC::OPCION3) SELECT = OPC::OPCION3;
            else{
                MenuOption::anteriorOpcion(SELECT);
                if(SELECT < OPC::OPCION3) SELECT = OPC::OPCION3;
            }

            break;
        case 1:
            ///funcionamiento de los botones
            break;
        case 0:
            //EXIT
            terminal.pintarRectangulo(34,2,27,84);
            return;
            break;
        }
    }
}

void AppManager::Config(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION1;
    int x = 4;
    int y = 5;

    terminal.pintarRectangulo(4,2,25,28);
    //terminal.pintarRectangulo(34,2,27,80);

    do{
        terminal.crearBoton("PRODUCTOS",x,y,SELECT == OPC::OPCION1);
        terminal.crearBoton("USUARIOS",x,y+3,SELECT == OPC::OPCION2);
        terminal.crearBoton("SEGURIDAD",x,y+6,SELECT == OPC::OPCION3);
        terminal.crearBoton("VOLVER",x,y+21,SELECT == OPC::OPCION4);

        switch(rlutil::getkey()){
        case 14:    ///sube
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION4;
            else MenuOption::anteriorOpcion(SELECT);
            break;
        case 15:    ///baja
            if(SELECT == OPC::OPCION4) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);
            break;
        case 1:     ///enter
            if(SELECT == OPC::OPCION1)MenuProductos();
            if(SELECT == OPC::OPCION2)MenuUsarios();
            if(SELECT == OPC::OPCION3)MenuCopiaSeg();

            if(SELECT == OPC::OPCION4){
                terminal.pintarRectangulo(4,2,27,27);
                return;
            }

            terminal.pintarRectangulo(4,2,27,27);
            TablaPrecios();

            break;
        }

    }while(true);
}

void AppManager::MenuProductos(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION1;
    int x = 4;
    int y = 5;

    terminal.pintarRectangulo(4,2,25,26);
    terminal.pintarRectangulo(34,2,27,82);

    do{
        terminal.crearBoton("MOSTRAR PRODUCTOS",x,y,SELECT == OPC::OPCION1);
        terminal.crearBoton("ALTA PRODUCTOS",x,y+3,SELECT == OPC::OPCION2);
        terminal.crearBoton("BAJA PRODUCTOS",x,y+6,SELECT == OPC::OPCION3);
        terminal.crearBoton("MODIFICAR STOCK",x,y+9,SELECT == OPC::OPCION4);
        terminal.crearBoton("MODIFICAR PRECIO",x,y+12,SELECT == OPC::OPCION5);
        terminal.crearBoton("VOLVER",x,y+21,SELECT == OPC::OPCION6);

        switch(rlutil::getkey()){
        case 14:    ///sube
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION6;
            else MenuOption::anteriorOpcion(SELECT);
            break;
        case 15:    ///baja
            if(SELECT == OPC::OPCION6) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);
            break;
        case 1:     ///enter
            if(SELECT == OPC::OPCION1)MostrarProductos();
            if(SELECT == OPC::OPCION2)AltaProd();
            if(SELECT == OPC::OPCION3)BajaProd();
            if(SELECT == OPC::OPCION4)ModStock();
            if(SELECT == OPC::OPCION5)ModPrecio();

            terminal.pintarRectangulo(34,2,27,80);

            if(SELECT == OPC::OPCION6)return;

            break;
        }

    }while(true);
}

void AppManager::MostrarProductos(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION_NULL;
    char arriba[2] = {(char)30,'\0'};
    char abajo[2] = {(char)31,'\0'};

    int posxColum1 = 35;
    int posxColum2 = 70;
    int posyInicial = 2;
    int cantArtListados = 0;
    int posx, posy, cantPos, posRegAct, cantPaginas;

    /** Busco la cantidad de registros a listar
        cantPos = arch.cantidadRegitros(); */

    posx = posxColum1;
    posy = posyInicial;


    terminal.crearBotonVertical(arriba,112,8,SELECT == OPC::OPCION1);
    terminal.crearBotonVertical(abajo,112,14,SELECT == OPC::OPCION2);

    for(int i=0; i<cantPos; i++){
        if(cantArtListados == 4){
            posx = posxColum2;
            posy = posyInicial;
            cantArtListados = 0;

        }else posx = posxColum1;

        /** obtiene el registro del archivo
            reg = arch.buscarRegistro(i); */

        terminal.mostrarTexto("ID:...............",posx,posy);
        ///terminal.mostrarTexto(reg.getId(),posx+20,posy);

        terminal.mostrarTexto("Nombre:...........",posx,posy+1);
        ///terminal.mostrarTexto(reg.getNombre(),posx+20,posy+1);

        terminal.mostrarTexto("Costo:...........$",posx,posy+2);
        ///terminal.mostrarTexto(reg.getCosto(),posx+20,posy+2);

        terminal.mostrarTexto("Precio:..........$",posx,posy+3);
        ///terminal.mostrarTexto(reg.getPrecio(),posx+20,posy+3);

        terminal.mostrarTexto("Stock:............",posx,posy+4);
        ///terminal.mostrarTexto(reg.getStock(),posx+20,posy+4);

        terminal.mostrarTexto("Estado:...........",posx,posy+5);
        ///terminal.mostrarTexto((reg.getEstado() == true ? "true":"false"),posx+20,posy+5);

        posy += 7;
        cantArtListados++;
    }


    rlutil::anykey();
    terminal.pintarRectangulo(34,2,27,84);
}

void AppManager::AltaProd(){
    Terminal terminal;
    const char select[2] = {(char)16,'\0'};

    OPC SELECT = OPC::OPCION_NULL;
    int posFlecha;
    bool status = true;


    terminal.pintarRectangulo(34,2,27,80);
    terminal.mostrarTexto("Tipo de Producto a cargar: ",35,5);

    while(status){
        terminal.mostrarTexto("BEBIDAS",80,5,SELECT == OPC::OPCION1);
        terminal.mostrarTexto("COMIDAS",100,5, SELECT == OPC::OPCION2);

        if(SELECT != OPC::OPCION_NULL)terminal.mostrarTexto(select,posFlecha,5);

        switch(rlutil::getkey()){
        case 16:
            terminal.pintarHorizontal(posFlecha,1,5);
            SELECT = OPC::OPCION1;
            posFlecha = 78;
            break;
        case 17:
            terminal.pintarHorizontal(posFlecha,1,5);
            SELECT = OPC::OPCION2;
            posFlecha = 98;
            break;
        case 1:
            if(SELECT == OPC::OPCION1) status = IngresoProdBebida();
            else status = IngresoProdComida();

            terminal.pintarRectangulo(34,6,23,84);

            break;
        }
    }
}

bool AppManager::IngresoProdBebida(){
    Terminal terminal;
    int posx = 35, posy = 8;

    OPC SELECT = OPC::OPCION_NULL;

    std::string nombre,costo,precio,variacion,volumen,gradAlcohol,stock;

    fflush(stdin);

    terminal.mostrarTexto("ID:.....................",posx,posy);
    terminal.mostrarTexto("NOMBRE:.................",posx,posy+2);
    terminal.mostrarTexto("COSTO:..................",posx,posy+4);
    terminal.mostrarTexto("PRECIO:.................",posx,posy+6);
    terminal.mostrarTexto("VARIACION:..............",posx,posy+8);
    terminal.mostrarTexto("VOLUMEN:................",posx,posy+10);
    terminal.mostrarTexto("GRADUACION ALCOHOL:.....",posx,posy+12);
    terminal.mostrarTexto("CANTIDAD EN STOCK:......",posx,posy+14);

    terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
    terminal.crearBoton("AGREGAR OTRO",62,25,SELECT == OPC::OPCION2);
    terminal.crearBoton("CANCELAR",89,25,SELECT == OPC::OPCION3);

    /**Tomar el valor de ID del archivo*/
    terminal.mostrarTexto("8AB23",posx+25,posy);

    nombre = terminal.ingresarTexto(posx+25,posy+2,true);
    costo = terminal.ingresarTexto(posx+25,posy+4,true);
    precio = terminal.ingresarTexto(posx+25,posy+6,true);
    variacion = terminal.ingresarTexto(posx+25,posy+8,true);
    volumen = terminal.ingresarTexto(posx+25,posy+10,true);
    gradAlcohol = terminal.ingresarTexto(posx+25,posy+12,true);
    stock = terminal.ingresarTexto(posx+25,posy+14,true);

    fflush(stdin);

    rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
    rlutil::setColor(rlutil::COLOR::WHITE);

    SELECT = OPC::OPCION1;

    while(true){

        terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
        terminal.crearBoton("AGREGAR OTRO",62,25,SELECT == OPC::OPCION2);
        terminal.crearBoton("CANCELAR",89,25,SELECT == OPC::OPCION3);

        switch(rlutil::getkey()){
        case 17:
            if(SELECT == OPC::OPCION3) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);

            break;
        case 16:
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION3;
            else MenuOption::anteriorOpcion(SELECT);

            break;
        case 1:
            if(SELECT == OPC::OPCION3) return false;


            /**     Ejemplo:

            1- Abrir archivo
            2- grabar el registro

            ArchivoArticulo arch;

            flag = arch.grabarRegistro(Articulo(id,nombre,costo,precio,stock,true));
            if(!flag) exit(223);
            */

            if(SELECT == OPC::OPCION1)return false;

            if(SELECT == OPC::OPCION2)return true;


            break;
        }
    }
}

bool AppManager::IngresoProdComida(){
    Terminal terminal;
    int posx = 35, posy = 8;

    OPC SELECT = OPC::OPCION_NULL;

    std::string nombre,observacion,guarnicion, costo,precio,variacion, stock;

    fflush(stdin);
    terminal.mostrarTexto("ID:.....................",posx,posy);
    terminal.mostrarTexto("NOMBRE:.................",posx,posy+2);
    terminal.mostrarTexto("COSTO:..................",posx,posy+4);
    terminal.mostrarTexto("PRECIO:.................",posx,posy+6);
    terminal.mostrarTexto("VARIACION:..............",posx,posy+8);
    terminal.mostrarTexto("OBSERVACION:............",posx,posy+10);
    terminal.mostrarTexto("GUARNICION:.............",posx,posy+12);
    terminal.mostrarTexto("CANTIDAD EN STOCK:......",posx,posy+14);

    terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
    terminal.crearBoton("AGREGAR OTRO",62,25,SELECT == OPC::OPCION2);
    terminal.crearBoton("CANCELAR",89,25,SELECT == OPC::OPCION3);

    terminal.mostrarTexto("8CE23",posx+25,posy);

    nombre = terminal.ingresarTexto(posx+25,posy+2,true);
    costo = terminal.ingresarTexto(posx+25,posy+4,true);
    precio = terminal.ingresarTexto(posx+25,posy+6,true);
    variacion = terminal.ingresarTexto(posx+25,posy+8,true);
    observacion = terminal.ingresarTexto(posx+25,posy+10,true);
    guarnicion = terminal.ingresarTexto(posx+25,posy+12,true);
    stock = terminal.ingresarTexto(posx+25,posy+14,true);

    fflush(stdin);

    SELECT = OPC::OPCION1;

    while(true){

        terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
        terminal.crearBoton("AGREGAR OTRO",62,25,SELECT == OPC::OPCION2);
        terminal.crearBoton("CANCELAR",89,25,SELECT == OPC::OPCION3);

        switch(rlutil::getkey()){
        case 17:
            if(SELECT == OPC::OPCION3) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);;

            break;
        case 16:
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION3;
            else MenuOption::anteriorOpcion(SELECT);

            break;
        case 1:
            if(SELECT == OPC::OPCION3) return false;

            /**     Ejemplo:

            1- Abrir archivo
            2- grabar el registro

            ArchivoArticulo arch;

            flag = arch.grabarRegistro(Articulo(id,nombre,costo,precio,stock,true));
            if(!flag) exit(223);
            */

            if(SELECT == OPC::OPCION1)return false;

            if(SELECT == OPC::OPCION2)return true;

            break;
        }
    }
}

void AppManager::BajaProd(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION_NULL;

    std::string id;
    int posReg = 1;
    int posx = 35;
    int posy = 8;
    bool status = false;

    terminal.mostrarTexto("Ingrese el ID del producto:",posx,5);
    terminal.crearBoton("ELIMINAR",35,25,SELECT == OPC::OPCION1);
    terminal.crearBoton("CANCELAR",65,25,SELECT == OPC::OPCION2);

    id = terminal.ingresarTexto(65,5,true);
    /** Ingreso de numero de ID a buscar:
        posReg = arch.buscarIndice(id); */

    if(posReg == -1){
        terminal.mostrarTexto("NO SE ENCOTRO EL ARCHIVO....",40,10);
        rlutil::anykey();
        terminal.pintarRectangulo(34,2,27,80);
        return;
    }

    /** Busco Registro en el archivo:
        reg = arch.buscarRegistro(posReg); */

    terminal.mostrarTexto("ID:...............",posx,posy);
    //terminal.mostrarTexto(reg.getId(),posx+20,posy);
    terminal.mostrarTexto("Nombre:...........",posx,posy+2);
    //terminal.mostrarTexto(reg.getNombre(),posx+20,posy+1);
    terminal.mostrarTexto("Costo:...........$",posx,posy+4);
    //terminal.mostrarTexto(reg.getCosto(),posx+20,posy+2);
    terminal.mostrarTexto("Precio:..........$",posx,posy+6);
    //terminal.mostrarTexto(reg.getPrecio(),posx+20,posy+3);
    terminal.mostrarTexto("Stock:............",posx,posy+8);
    //terminal.mostrarTexto(reg.getStock(),posx+20,posy+4);
    terminal.mostrarTexto("Estado:...........",posx,posy+10);
    //terminal.mostrarTexto((reg.getEstado() == true ? "true":"false"),posx+20,posy+5);

    rlutil::setBackgroundColor(rlutil::COLOR::RED);
    terminal.mostrarTexto(" ESTA SEGURO QUE DESEA DAR DE BAJA ESTE ARTICULO? ",posx,posy+14);
    rlutil::setBackgroundColor(rlutil::COLOR::BLACK);

    SELECT = OPC::OPCION1;

    while(true){

        terminal.crearBoton("ELIMINAR",35,25,SELECT == OPC::OPCION1);
        terminal.crearBoton("CANCELAR",65,25,SELECT == OPC::OPCION2);

        switch(rlutil::getkey()){
        case 16:
            SELECT = OPC::OPCION1;
            break;
        case 17:
            SELECT = OPC::OPCION2;
            break;
        case 1:

            if(SELECT == OPC::OPCION2)return;

            /**     Cambiar el estado del registro para hacer la baja logica
            reg.setEstado(false);
            status = arch.modificacionRegistro(reg,posReg);*/

            terminal.pintarHorizontal(posx,50,posy+14);

            if(!status) terminal.mostrarTexto("Eliminacion Exitosa",posx,posy+14);
            else{
                terminal.mostrarTexto("Fallo durantela el borrado del archivo",posx,posy+14);
            }

            rlutil::anykey();
            fflush(stdin);
            return;
        }
    }
}

void AppManager::ModStock(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION_NULL;

    std::string id, nuevoPrecio;
    int posReg = 1;
    int posx = 35;
    int posy = 8;

    terminal.mostrarTexto("Ingrese el ID del producto:",posx,5);
    terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
    terminal.crearBoton("CANCELAR",65,25,SELECT == OPC::OPCION2);

    id = terminal.ingresarTexto(65,5,true);

    terminal.mostrarTexto("ID:...............",posx,posy);
    terminal.mostrarTexto(id,posx+20,posy);                     /// --> provisorio, debe buscar en archivo;
    terminal.mostrarTexto("Nombre:...........",posx,posy+2);
    terminal.mostrarTexto("Costo:...........$",posx,posy+4);
    terminal.mostrarTexto("Precio:..........$",posx,posy+6);
    terminal.mostrarTexto("Stock:............",posx,posy+8);
    terminal.mostrarTexto("Estado:...........",posx,posy+10);

    terminal.mostrarTexto("Ingrese el nuevo monto deseado: ",posx,posy+14,true);
    nuevoPrecio = terminal.ingresarTexto(posx+33,posy+14,true);

    SELECT = OPC::OPCION1;

    while(true){

        terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
        terminal.crearBoton("CANCELAR",65,25,SELECT == OPC::OPCION2);

        switch(rlutil::getkey()){
        case 16:
            SELECT = OPC::OPCION1;
            break;
        case 17:
            SELECT = OPC::OPCION2;
            break;
        case 1:

            if(SELECT == OPC::OPCION2)return;

            /**RAELIZAR CAMBIOS EN EL ARCHIVO CORRESPONDIENTE*/

            terminal.pintarHorizontal(posx,50,posy+14);
            bool status = false;

            if(!status) terminal.mostrarTexto("Modificacion Exitosa",posx,posy+14,true);
            else{
                terminal.mostrarTexto("Fallo durantela la modificacion del archivo",posx,posy+14,true);
            }

            rlutil::anykey();
            return;
        }
    }
}

void AppManager::ModPrecio(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION_NULL;

    std::string id, nuevoStock;
    int posReg = 1;
    int posx = 35;
    int posy = 8;

    terminal.mostrarTexto("Ingrese el ID del producto:",posx,5);
    terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
    terminal.crearBoton("CANCELAR",65,25,SELECT == OPC::OPCION2);

    id = terminal.ingresarTexto(65,5,true);

    terminal.mostrarTexto("ID:...............",posx,posy);
    terminal.mostrarTexto(id,posx+20,posy);                     /// --> provisorio, debe buscar en archivo;
    terminal.mostrarTexto("Nombre:...........",posx,posy+2);
    terminal.mostrarTexto("Costo:...........$",posx,posy+4);
    terminal.mostrarTexto("Precio:..........$",posx,posy+6);
    terminal.mostrarTexto("Stock:............",posx,posy+8);
    terminal.mostrarTexto("Estado:...........",posx,posy+10);

    terminal.mostrarTexto("Ingrese el nuevo stock deseado: ",posx,posy+14,true);
    nuevoStock = terminal.ingresarTexto(posx+33,posy+14,true);

    SELECT = OPC::OPCION1;

    while(true){

        terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
        terminal.crearBoton("CANCELAR",65,25,SELECT == OPC::OPCION2);

        switch(rlutil::getkey()){
        case 16:
            SELECT = OPC::OPCION1;
            break;
        case 17:
            SELECT = OPC::OPCION2;
            break;
        case 1:

            if(SELECT == OPC::OPCION2)return;

            /**RAELIZAR CAMBIOS EN EL ARCHIVO CORRESPONDIENTE*/

            terminal.pintarHorizontal(posx,50,posy+14);
            bool status = false;

            if(!status) terminal.mostrarTexto("Modificacion Exitosa",posx,posy+14,true);
            else{
                terminal.mostrarTexto("Fallo durantela la modificacion del archivo",posx,posy+14,true);
            }

            rlutil::anykey();
            return;
        }
    }
}

void AppManager::MenuUsarios(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION1;
    int x = 4;
    int y = 5;

    terminal.pintarRectangulo(4,2,25,26);
    terminal.pintarRectangulo(34,2,27,82);

    do{
        terminal.crearBoton("MOSTRAR USUARIOS",x,y,SELECT == OPC::OPCION1);
        terminal.crearBoton("ALTA USUARIO",x,y+3,SELECT == OPC::OPCION2);
        terminal.crearBoton("BAJA USUARIO",x,y+6,SELECT == OPC::OPCION3);
        terminal.crearBoton("MODIFICAR USUARIO",x,y+9,SELECT == OPC::OPCION4);
        terminal.crearBoton("VOLVER",x,y+21,SELECT == OPC::OPCION5);

        switch(rlutil::getkey()){
        case 14:    ///sube
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION5;
            else MenuOption::anteriorOpcion(SELECT);
            break;
        case 15:    ///baja
            if(SELECT == OPC::OPCION5) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);
            break;
        case 1:     ///enter
            if(SELECT == OPC::OPCION1)MostrarUsuarios();
            if(SELECT == OPC::OPCION2)AltaUsuario();
            if(SELECT == OPC::OPCION3)BajaUsuario();

            terminal.pintarRectangulo(34,2,27,80);

            if(SELECT == OPC::OPCION5){
                terminal.pintarRectangulo(4,2,27,27);
                return;
            }

            break;
        }

    }while(true);
}

void AppManager::MostrarUsuarios(){
    Terminal terminal;
}

void AppManager::AltaUsuario(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION_NULL;

    int posx = 55, posy = 6;
    int posFlecha = posx + 33;
    const char select[2] = {(char)16,'\0'};
    bool status = true;

    std::string nombre,apellido,diaNac,mesNac,anioNac,legajo,categoria,pass;

    /// opcional
    ///std::string diaIng,mesIng,anioIng;

    terminal.mostrarTexto("Ingrese los datos del Usuario:",posx,3);

    terminal.mostrarTexto("LEGAJO:.....................",posx,posy);
    terminal.mostrarTexto("NOMBRE:.....................",posx,posy+2);
    terminal.mostrarTexto("APELLIDO:...................",posx,posy+4);
    terminal.mostrarTexto("FECHA DE NACIMIENTO:",posx,posy+6);
    terminal.mostrarTexto("DIA.........................",posx,posy+8);
    terminal.mostrarTexto("MES:........................",posx,posy+10);
    terminal.mostrarTexto("ANIO:.......................",posx,posy+12);
    terminal.mostrarTexto("CONTRASENIA:................",posx,posy+14);
    terminal.mostrarTexto("CATEGORIA:..................",posx,posy+16);

    terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
    terminal.crearBoton("CANCELAR",62,25,SELECT == OPC::OPCION2);

    /**Tomar el valor de ID del archivo*/
    terminal.mostrarTexto("1234",posx+35,posy);


    nombre = terminal.ingresarTexto(posx+35,posy+2,true);
    apellido = terminal.ingresarTexto(posx+35,posy+4,true);
    diaNac = terminal.ingresarTexto(posx+35,posy+8,true);
    mesNac = terminal.ingresarTexto(posx+35,posy+10,true);
    anioNac = terminal.ingresarTexto(posx+35,posy+12,true);
    pass = terminal.ingresarTexto(posx+35,posy+14,true);

    SELECT = OPC::OPCION1;

    while(status){
        terminal.mostrarTexto("SUPERVISOR",posx+35,posy+16,SELECT == OPC::OPCION1);
        terminal.mostrarTexto("CAJERO",posx+50,posy+16,SELECT == OPC::OPCION2);

        terminal.mostrarTexto(select,posFlecha,posy+16);

        switch(rlutil::getkey()){
        case 16:
            terminal.pintarHorizontal(posFlecha,1,posy+16);
            SELECT = OPC::OPCION1;
            posFlecha = posx + 33;
            break;
        case 17:
            terminal.pintarHorizontal(posFlecha,1,posy+16);
            SELECT = OPC::OPCION2;
            posFlecha = posx + 48;
            break;
        case 1:
            ///guardar categoria de acceso;
            status = false;
        }
    }

    SELECT = OPC::OPCION1;

    while(true){

        terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
        terminal.crearBoton("CANCELAR",62,25,SELECT == OPC::OPCION2);

        switch(rlutil::getkey()){
        case 17:
            if(SELECT == OPC::OPCION2) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);

            break;
        case 16:
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION2;
            else MenuOption::anteriorOpcion(SELECT);

            break;
        case 1:

            if(SELECT == OPC::OPCION2) return;

            /**     Ejemplo:

            1- Abrir archivo
            2- grabar el registro

            */

            return;
        }
    }

}

void AppManager::BajaUsuario(){

}

void AppManager::MenuCopiaSeg(){
Terminal terminal;
    OPC SELECT = OPC::OPCION1;
    int x = 4;
    int y = 5;

    terminal.pintarRectangulo(4,2,25,28);
    terminal.pintarRectangulo(34,2,27,82);

    do{
        terminal.crearBoton("GENERAR BACKUP",x,y,SELECT == OPC::OPCION1);
        terminal.crearBoton("CARGAR BACKUP",x,y+3,SELECT == OPC::OPCION2);
        terminal.crearBoton("VOLVER",x,y+21,SELECT == OPC::OPCION3);

        switch(rlutil::getkey()){
        case 14:    ///sube
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION3;
            else MenuOption::anteriorOpcion(SELECT);
            break;
        case 15:    ///baja
            if(SELECT == OPC::OPCION3) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);
            break;
        case 1:     ///enter
            if(SELECT == OPC::OPCION1)GenerarBackup();
            if(SELECT == OPC::OPCION2)CargarBackup();

            if(SELECT == OPC::OPCION3){
                terminal.pintarRectangulo(4,2,27,27);
                return;
            }

            break;
        }

    }while(true);
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

void AppManager::TablaPrecios(){

    Cuadro grafico(28,9,2,34);
    Terminal terminal;

    char alta[8] = {' ',' ',' ',' ',' ',' ',(char)30,'\0'};
    char baja[8] = {' ',' ',' ',' ',' ',' ',(char)31,'\0'};
    bool status = false;
    rlutil::COLOR indicador;


    /*****************Datos de prueba**************************/

    std::string bebidas[10]={
        "Whisky","Cerveza","Vinos",
        "Espumantes","Vodka","Ron",
        "Aperitivos","Tragos",
        "Cocteles","Comida"
    };

    int elem[10] = {3,5,4,6,4,2,7,5,8,5};
    int tam = 10;                           //editar con mem dinamica

    /**********************************************************/

    terminal.pintarRectangulo(34,2,0,82,rlutil::COLOR::LIGHTRED);
    grafico.agregarColumna("Bebida",0,3,rlutil::COLOR::LIGHTRED);
    grafico.agregarColumna(" %Osc ",1,3,rlutil::COLOR::LIGHTRED);
    grafico.agregarColumna("PreUlt",2,5,rlutil::COLOR::LIGHTRED);

    grafico.agregarColumna("Bebida",3,3,rlutil::COLOR::LIGHTRED);
    grafico.agregarColumna(" %Osc ",4,3,rlutil::COLOR::LIGHTRED);
    grafico.agregarColumna("PreUlt",5,5,rlutil::COLOR::LIGHTRED);

    grafico.agregarColumna("Bebida",6,3,rlutil::COLOR::LIGHTRED);
    grafico.agregarColumna(" %Osc ",7,3,rlutil::COLOR::LIGHTRED);
    grafico.agregarColumna("PreUlt",8,5,rlutil::COLOR::LIGHTRED);

    for(int i=0; i<tam; i++){

        grafico.escribirFila(bebidas[i],grafico.getColActual(), rlutil::COLOR::LIGHTCYAN);
        grafico.saltoFila();
        grafico.escribirFila("------------------------",grafico.getColActual());
        grafico.saltoFila();

        for(int j=0; j<elem[i]; j++){

            if(status) indicador = rlutil::COLOR::GREEN;
            else indicador = rlutil::COLOR::RED;

            grafico.escribirFila("alcohol",grafico.getColActual());
            ///momentaneo
            grafico.escribirFila((status == true ? alta : baja),grafico.getColActual() + 1, indicador);
            grafico.escribirFila(" %1.25",grafico.getColActual() + 1, indicador);
            grafico.escribirFila("$125.5",grafico.getColActual() + 2);

            status = !status;

            if(grafico.saltoFila() == false){
                if(!grafico.saltoColum(grafico.getColActual() + 3)) break;
            }
        }

        if(grafico.saltoFila() == false){
            if(!grafico.saltoColum(grafico.getColActual() + 3)) break;
        }
    }
}

