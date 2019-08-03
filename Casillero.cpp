#include "Casillero.h"

Casillero::Casillero(int posX, int posY)
{
    this->posX = posX;
    this->posY = posY;
    this->ocupado = false;
}


void Casillero::setOcupante(Tropa* nuevaTropa)//ocupar
{
    this->cambiarOcupado();
    this->tropaOcupante = nuevaTropa;

}

void Casillero::desocupar()
{
    this->cambiarOcupado();
    this->tropaOcupante = nullptr;
}


Tropa* Casillero::getTropaOcupante()
{
    return this->tropaOcupante;
}

bool Casillero::casilleroOcupado()
{
    return this->ocupado;
}

void Casillero::cambiarOcupado()
{
  this->ocupado = !this->ocupado;

}

int Casillero::getPosX()
{
    return this->posX;
}

int Casillero::getPosY()
{
    return this->posY;
}

void Casillero::setPosX(int nuevaPosX)
{
    this->posX = nuevaPosX;
}

void Casillero::setPosY(int nuevaPosY)
{
    this->posY = nuevaPosY;
}

void Casillero::setNuevaPos(int nuevoX,int nuevoY)
{
    this->posX = nuevoX;
    this->posY = nuevoY;

}

void Casillero::imprimirPos()
{
    std::cout<<"["<<this->getPosX()<<","<< this->getPosY()<<"]"<<std::endl;
}
