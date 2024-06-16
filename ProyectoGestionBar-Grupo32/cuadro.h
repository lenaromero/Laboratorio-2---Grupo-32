#pragma once
#include <iostream>
#include "Terminal.h"


class Cuadro{
private:

    int x_Ini;
    int y_Ini;

    int maxCol;
    int maxFila;

    int* posFilas;
    int* posColum;

    int filaAct;
    int columAct;

    Terminal terminal;

    void cargarPosiciones(int filas, int col);

public:

    Cuadro(int filas, int columnas, int posyIni, int posxIni);
    ~Cuadro();

    int getColActual();
    int getFilaActual();

    void agregarColumna(std::string nombre, int numCol, int separacion, rlutil::COLOR cBack = rlutil::COLOR::BLACK);
    void escribirFila(std::string texto, int posCol, rlutil::COLOR cText = rlutil::COLOR::WHITE);

    bool saltoFila();
    bool saltoFila(int fila);
    bool saltoColum();
    bool saltoColum(int col);



};
