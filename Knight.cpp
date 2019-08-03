#include "Knight.h"

Knight::Knight(ColorJugador unColor)
{
      this->nombre = "Knight";
      this->ID = "K";
      this->vida = 210;
      this->ataque = 90;
      this->vision = 1;
      this->color = unColor;
      this->misMovimientos = new ListaSE<Casillero*>();
      this->primerMovimiento = false;
}

Knight::~Knight()
{
    this->misMovimientos->conocerCursor()->reiniciarCursor();
    while(this->misMovimientos->conocerCursor()->avanzarCursor())
    {
        delete this->misMovimientos->conocerCursor()->obtenerCursor();
    }
    delete this->misMovimientos;
}

void Knight::atacar(Tropa* objetivo)
{
     objetivo->recibirDanio(this->ataque);

}

void Knight::crearMovimientos()
{
    int x,y;
    x = this->getPosX();
    y = this->getPosY();

    this->misMovimientos->agregar(new Casillero(x-1,y-2)); //ARRIBA IZQ 1
    this->misMovimientos->agregar(new Casillero(x-2,y-1));//ARRIBA IZQ 2
    this->misMovimientos->agregar(new Casillero(x+1,y-2));//ARRIBA DER 1
    this->misMovimientos->agregar(new Casillero(x+2,y-1));//ARRIBA DER 2
    this->misMovimientos->agregar(new Casillero(x-2,y+1));//ABAJO IZQ 1
    this->misMovimientos->agregar(new Casillero(x-1,y+2));//ABAJO IZQ 2
    this->misMovimientos->agregar(new Casillero(x+1,y+2));//ABAJO DER 1
    this->misMovimientos->agregar(new Casillero(x+2,y+1));//ABAJO DER 2
}

void Knight::actualizarMovimientos()//actualiza todos los movimientos posibles que puede hacer la tropa,según la pos actual
{
    int pos = 0;
    int x,y;
    x = this->getPosX();
    y = this->getPosY();

    Casillero* casillero;

    this->misMovimientos->conocerCursor()->reiniciarCursor();
    while(this->misMovimientos->conocerCursor()->avanzarCursor())
    {
       casillero=this->misMovimientos->conocerCursor()->obtenerCursor();

       if(pos == 0)
       {
         casillero->setNuevaPos(x-1,y-2);//ARRIBA IZQ 1
       }
       else if(pos == 1)
       {
         casillero->setNuevaPos(x-2,y-1);//ARRIBA IZQ 2
       }
       else if(pos == 2)
       {
         casillero->setNuevaPos(x+1,y-2);//ARRIBA DER 1
       }
       else if(pos == 3)
       {
         casillero->setNuevaPos(x+2,y-1);//ARRIBA DER 2
       }
       else if(pos == 4)
       {
         casillero->setNuevaPos(x-2,y+1);//ABAJO IZQ 1
       }
       else if(pos == 5)
       {
         casillero->setNuevaPos(x-1,y+2);//ABAJO IZQ 2
       }
       else if(pos == 6)
       {
         casillero->setNuevaPos(x+1,y+2);//ABAJO DER 1
       }
       else if(pos == 7)
       {
         casillero->setNuevaPos(x+2,y+1);//ABAJO DER 2
       }

        pos++;

    }
}

bool Knight::crearOActualizar()
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
