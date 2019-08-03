#include "Tropa.h"

std::string Tropa::getNombre()
{
    return this->nombre;
}

std::string Tropa::getID()
{
    return this->ID;
}


bool Tropa::getPrimerMovimiento()
{
    return this->primerMovimiento;
}

void Tropa::cambiarPrimerMovimiento()
{
    this->primerMovimiento = !this->primerMovimiento;
}

int Tropa::getVida()
{
    return this->vida;
}

int Tropa::getAtaque()
{
    return this->ataque;
}

void Tropa::recibirDanio(int danio)
{
    this->vida-=danio;
}

int Tropa::getVision()
{
   return this->vision;

}

void Tropa::cambiarVision(int nuevaVision)
{
    this->vision = nuevaVision;
}

int Tropa::getPosX()
{
    return this->posX;
}

int Tropa::getPosY()
{
    return this->posY;
}

void Tropa::setPosX(int nuevaPosX)
{
    this->posX = nuevaPosX;
}

void Tropa::setPosY(int nuevaPosY)
{
    this->posY = nuevaPosY;
}

ColorJugador Tropa::getColor()
{
    return this->color;
}

int Tropa::totalMovimientos()
{
     int total;
     total = this->misMovimientos->contarElementos();
     return total;
}

Casillero* Tropa::obtenerMovimiento(int t)
{
    Casillero* casillero;
    casillero = this->misMovimientos->obtenerElemento(t);
    return casillero;
}


void Tropa::cambiarAtaque(int nuevoAtaque)
{
    this->ataque = nuevoAtaque;
}

bool Tropa::getMovio()
{
  return this->movio;

}

void Tropa::cambiarMovio()
{
    this->movio = !this->movio;
}

bool Tropa::evaluarMiMovimiento(int x, int y)//este metodo chequea solo si esta dentro de mi lista de movs posibles
{
    Casillero* casillero;//no chequea si esta fuera de rango u ocupado

    this->misMovimientos->conocerCursor()->reiniciarCursor();
    while(this->misMovimientos->conocerCursor()->avanzarCursor())
    {
        casillero = this->misMovimientos->conocerCursor()->obtenerCursor();

        if(casillero->getPosX() == x && casillero->getPosY() == y)
        {
             return true;
        }

    }
    return false;
}









