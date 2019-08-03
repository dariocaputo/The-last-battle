#ifndef CASILLERO_H_INCLUDED
#define CASILLERO_H_INCLUDED
#include <iostream>
#include "Tropa.h"

class Tropa;

class Casillero
{

private:

    int posX, posY;
    bool ocupado;
    Tropa* tropaOcupante;

public:

    Casillero(int posX, int posY);//constructor
    int getPosX();
    int getPosY();
    void imprimirPos();
    void setPosX(int nuevaPosX);
    void setPosY(int nuevaPosY);
    void setNuevaPos(int nuevoX,int nuevoY);
    bool casilleroOcupado();
    void setOcupante(Tropa* nuevaTropa);
    void desocupar();
    Tropa* getTropaOcupante();
    void cambiarOcupado();

};

#endif // CASILLERO_H_INCLUDED
