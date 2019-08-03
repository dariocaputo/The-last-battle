#include "Contendiente.h"

Contendiente::Contendiente(ColorJugador unColor)
{
      this->nombre = "Contendiente";
      this->ID = "C";
      this->vida = 120;
      this->ataque = 30;
      this->vision = 1;
      this->color = unColor;
      this->misMovimientos = new ListaSE<Casillero*>();
      this->primerMovimiento = false;
}

Contendiente::~Contendiente()
{
    this->misMovimientos->conocerCursor()->reiniciarCursor();
    while(this->misMovimientos->conocerCursor()->avanzarCursor())
    {
        delete this->misMovimientos->conocerCursor()->obtenerCursor();

    }
    delete this->misMovimientos;
}


void Contendiente::atacar(Tropa* objetivo)
{
  objetivo->recibirDanio(this->ataque);
  this->ataque+=10;//cada vez que ataco se incrementa mi ataque en 10 unidades.

}

void Contendiente::crearMovimientos()
{
    int x,y;
    x = this->getPosX();
    y = this->getPosY();

    this->misMovimientos->agregar(new Casillero(x+1,y)); //DERECHA
    this->misMovimientos->agregar(new Casillero(x-1,y));//IZQUIERDA
    this->misMovimientos->agregar(new Casillero(x,y-1));//ARRIBA
    this->misMovimientos->agregar(new Casillero(x,y+1));//ABAJO
}

void Contendiente::actualizarMovimientos()//actualiza todos los movimientos posibles que puede hacer la tropa,segun la pos actual
{
    int pos = 0;
    int x = this->getPosX();
    int y = this->getPosY();

    Casillero* casillero;

    this->misMovimientos->conocerCursor()->reiniciarCursor();
    while(this->misMovimientos->conocerCursor()->avanzarCursor())
    {
        casillero = this->misMovimientos->conocerCursor()->obtenerCursor();
       if(pos == 0)
       {
         casillero->setNuevaPos(x+1,y);//DERECHA
       }
       else if(pos == 1)
       {
         casillero->setNuevaPos(x-1,y);//IZQU
       }
       else if(pos == 2)
       {
         casillero->setNuevaPos(x,y-1);//ARRIBA
       }
       else if(pos == 3)
       {
         casillero->setNuevaPos(x,y+1);//ABAJO
       }
        pos++;

    }

}

bool Contendiente::crearOActualizar()
{
      if(this->getPrimerMovimiento()==false)
      {
          this->crearMovimientos();//se crea la lista con todas las coordenadas
          this->cambiarPrimerMovimiento();//de esta forma al elegir a otro arquero del mismo equipo u otro personaje, se crean los mov
      }
      else if(this->getPrimerMovimiento())
      {
          this->actualizarMovimientos();//ya no se crea de nuevo la lista de mov, solamente se actualiza
      }
   return true;
}
