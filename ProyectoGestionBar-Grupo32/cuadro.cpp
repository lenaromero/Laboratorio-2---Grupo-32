#include "cuadro.h"
#include <cstring>

void Cuadro::cargarPosiciones(int filas, int col){

    posFilas = new int[filas];
    posColum = new int[col];

    for(int i=0; i<filas; i++){
        posFilas[i] = y_Ini + i;
    }

    posColum[0] = x_Ini;

    filaAct = 1;
    columAct = 0;

}

Cuadro::Cuadro(int filas, int columnas, int posyIni, int posxIni){
    x_Ini = posxIni;
    y_Ini = posyIni;
    maxCol = columnas;
    maxFila = filas;

    cargarPosiciones(filas, columnas);
}

Cuadro::~Cuadro(){
    delete []posFilas;
    delete []posColum;
}

int Cuadro::getColActual(){return columAct;}
int Cuadro::getFilaActual(){return filaAct;}

void Cuadro::agregarColumna(std::string nombre, int numCol, int separacion, rlutil::COLOR cBack){

    if(numCol < 0 || numCol >= maxCol) return;

    rlutil::setBackgroundColor(cBack);
    terminal.mostrarTexto(nombre,posColum[numCol],posFilas[0]);

    int posAct = posColum[numCol];
    if(numCol != maxCol) posColum[numCol+1] = posAct + strlen(nombre.c_str()) + separacion;

    rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
}

void Cuadro::escribirFila(std::string texto, int posCol, rlutil::COLOR cText){

    if(columAct == maxCol)return;

    rlutil::setColor(cText);

    if(filaAct < maxFila){
        terminal.mostrarTexto(texto,posColum[posCol],posFilas[filaAct]);
    }

    rlutil::setColor(rlutil::COLOR::WHITE);
}

bool Cuadro::saltoFila(){

    if(filaAct < maxFila){
        filaAct++;
        return true;
    }

    return false;
}

bool Cuadro::saltoFila(int fila){

    if(fila >= 0 && fila <= maxFila){
        filaAct = fila;
        return true;
    }

    return false;
}

bool Cuadro::saltoColum(){
    if(columAct < maxCol){
        columAct++;
        filaAct = 1;
        return true;
    }

    return false;
}

bool Cuadro::saltoColum(int col){
    if(col >= 0 && col <= maxCol){
        columAct = col;
        filaAct = 1;
        return true;
    }

    return false;
}



