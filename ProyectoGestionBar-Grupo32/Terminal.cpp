#include "Terminal.h"
#include <cstring>

void Terminal::mostrarTexto(std::string text, int x, int y){
    rlutil::hidecursor();       //esconde el cursor
    rlutil::locate(x,y);
    std::cout<<text;
}

std::string Terminal::ingresarTexto(int x, int y, bool cursorOn){
    std::string text = "NULL";

    if(cursorOn) rlutil::CursorHider();
    else rlutil::hidecursor();

    rlutil::locate(x,y);
    getline(std::cin,text);

    return text;
}

void Terminal::pintarHorizontal(int x, int largo, int y){
    rlutil::locate(x,y);

    for(int i=0; i<largo; i++){
        std::cout<<" ";
    }
}

void Terminal::barraEspera(int time){

    for(int i=0; i<7; i++){
        rlutil::msleep(time);
        std::cout<<". ";
    }
}

void Terminal::barraEspera(int time, int x, int y){
    int aux = time/35;
    rlutil::setBackgroundColor(rlutil::COLOR::CYAN);


    for(int i=0; i<35; i++){
        rlutil::msleep(time);
        mostrarTexto(" ",x-8+i,y);
        time -= aux;
    }

    rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
}

void Terminal::dibujarRectangulo(int x, int y, int alto, int ancho){
    COORD coord;

    for (int i = 0; i < alto; i++) {

		for (int j = 0; j < ancho; j++) {

            coord.X = x+j;
            coord.Y = y+i;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);

			if (i == 0 && j == 0)std::cout << char(201);
			if (i == 0 && j == ancho - 1)std::cout << char(187);

			if (i == alto - 1 && j == 0)std::cout << char(200);
			if (i == alto - 1 && j == ancho - 1)std::cout << char(188);

			if ((j == 0 || j == ancho - 1) && i > 0 && i < alto - 1){
                std::cout << char(186);//179
            }
			if ((i == 0 || i == alto - 1) && j > 0 && j < ancho - 1){
				std::cout << char(205);//196
			}
		}
	}
}

void Terminal::pintarRectangulo(int x, int y, int alto, int ancho){

    for(int i=y; i<=y+alto; i++){
        pintarHorizontal(x,ancho,i);
    }

}

void Terminal::pintarRectangulo(int x, int y, int alto, int ancho, rlutil::COLOR cFondo){
    rlutil::setBackgroundColor(cFondo);

    for(int i=y; i<=y+alto; i++){
        pintarHorizontal(x,ancho,i);
    }

    rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
}

void Terminal::crearBoton(std::string text, int x, int y, bool select){
    int tam = strlen(text.c_str());
    int x_text = (x+13)-(tam/2);

    if(select)rlutil::setBackgroundColor(rlutil::COLOR::LIGHTBLUE);

    dibujarRectangulo(x,y,3,26);
    pintarHorizontal(x+2,24,y+2);
    mostrarTexto(text,x_text,y+2);

    rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
}

void Terminal::crearBotonVertical(std::string text, int x, int y, bool select){
    if(select)rlutil::setBackgroundColor(rlutil::COLOR::LIGHTBLUE);

    dibujarRectangulo(x,y,5,5);
    pintarRectangulo(x+2,y+2,2,3);
    mostrarTexto(text,x+3,y+3);

    rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
}

void Terminal::crearColumna(std::string texto,rlutil::COLOR cFondo, int x, int y, bool separacion){
    int y_max = 30;
    int x_final = x + strlen(texto.c_str()) + 1;
    rlutil::setBackgroundColor(cFondo);

    mostrarTexto(texto,x,y);

    rlutil::setBackgroundColor(rlutil::COLOR::BLACK);

    if(!separacion) return;

    for(int i=y; i<y_max; i++){
        mostrarTexto("|",x_final,i);
    }
}

void Terminal::crearFila(std::string text,rlutil::COLOR cTexto, int x, int y){
    rlutil::setColor(cTexto);
    mostrarTexto(text,x,y);
    rlutil::setColor(rlutil::COLOR::WHITE);
}


