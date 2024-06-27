#pragma once
#include "rlutil.h"
#include <windows.h>
#include <iostream>

class Terminal{
public:

    void mostrarTexto(std::string text, int x, int y);
    void mostrarTexto(float numero, int x, int y);
    void mostrarTexto(std::string text, int x, int y, bool resaltar);

    std::string ingresarTexto(int x, int y, bool cursorOn);
    float ingresarNumero(int x, int y, bool cursorOn);

    void pintarHorizontal(int x, int largo, int y);
    void barraEspera(int time, int x, int y);
    void dibujarRectangulo(int init_x, int init_y, int largo, int ancho);
    void dibujarRectanguloSimple(int init_x, int init_y, int largo, int ancho);
    void pintarRectangulo(int x, int y, int alto, int ancho);
    void pintarRectangulo(int x, int y, int alto, int ancho, rlutil::COLOR cFondo);
    void crearBoton(std::string text, int x, int y, bool select);
    void crearBotonVertical(std::string text, int x, int y, bool select);

    void textBox(int x, int largo, int y, rlutil::COLOR cBack);
};
