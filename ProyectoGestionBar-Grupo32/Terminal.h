#pragma once
#include "rlutil.h"
#include <windows.h>
#include <iostream>

class Terminal{
public:

    void mostrarTexto(std::string text, int x, int y);
    std::string ingresarTexto(int x, int y, bool cursorOn);
    void pintarHorizontal(int x, int largo, int y);
    void barraEspera(int time);                             //eliminar?
    void barraEspera(int time, int x, int y);
    void dibujarRectangulo(int init_x, int init_y, int largo, int ancho);
    void pintarRectangulo(int x, int y, int alto, int ancho);
    void pintarRectangulo(int x, int y, int alto, int ancho, rlutil::COLOR cFondo);

    void crearBoton(std::string text, int x, int y, bool select);
    void crearBotonVertical(std::string text, int x, int y, bool select);
    void crearColumna(std::string text,rlutil::COLOR cFondo, int x, int y, bool separacion);
    void crearFila(std::string text,rlutil::COLOR cTexto, int x, int y);
};
