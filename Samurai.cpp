#include "Samurai.h"

Samurai::Samurai(ColorJugador unColor)
{
      this->nombre = "Samurai";
      this->ID = "S";
      this->vida = 80;
      this->ataque = this->vida;
      this->vision = 1;
      this->color = unColor;
      this->misMovimientos = new ListaSE<Casillero*>();
      this->primerMovimiento = false;
}

Samurai::~Samurai()
{
    this->misMovimientos->conocerCursor()->reiniciarCursor();
    while(this->misMovimientos->conocerCursor()->avanzarCursor())
    {
        delete this->misMovimientos->conocerCursor()->obtenerCursor();

    }
    delete this->misMovimientos;
}

void Samurai::atacar(Tropa* objetivo)
{
   objetivo->recibirDanio(this->ataque);

}

void Samurai::crearMovimientos()
{
    int x,y;
    x = this->getPosX();
    y = this->getPosY();

    this->misMovimientos->agregar(new Casillero(x+2,y)); //DERECHA
    this->misMovimientos->agregar(new Casillero(x-2,y));//IZQUIERDA
    this->misMovimientos->agregar(new Casillero(x,y-2));//ARRIBA
    this->misMovimientos->agregar(new Casillero(x,y+2));//ABAJO
    this->misMovimientos->agregar(new Casillero(x-2,y-2));//ARRIBA IZQ
    this->misMovimientos->agregar(new Casillero(x+2,y-2));//ARRIBA DER
    this->misMovimientos->agregar(new Casillero(x-2,y+2));//ABAJO IZQ
    this->misMovimientos->agregar(new Casillero(x+2,y+2));//ABAJO DER
}

void Samurai::actualizarMovimientos()//actualiza todos los movimientos posibles que puede hacer la tropa,segun la pos actual
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
         casillero->setNuevaPos(x+2,y);//DERECHA
       }
       else if(pos == 1)
       {
         casillero->setNuevaPos(x-2,y);//IZQU
       }
       else if(pos == 2)
       {
         casillero->setNuevaPos(x,y-2);//ARRIBA
       }
       else if(pos == 3)
       {
         casillero->setNuevaPos(x,y+2);//ABAJO
       }
       else if(pos == 4)
       {
         casillero->setNuevaPos(x-2,y-2);//ARRIBA IZQ
       }
       else if(pos == 5)
       {
         casillero->setNuevaPos(x+2,y-2);//ARRIBA DER
       }
       else if(pos == 6)
       {
         casillero->setNuevaPos(x-2,y+2);//ABAJO IZQ
       }
       else if(pos == 7)
       {
         casillero->setNuevaPos(x+2,y+2);//ABAJO DER
       }

        pos++;
    }

}

bool Samurai::crearOActualizar()
{
      if(this->getPrimerMovimiento()==false)
      {
          this->crearMovimientos();//se crea la lista con todas las coordenadas
          this->cambiarPrimerMovimiento();//de esta forma al elegir a otro arquero del mismo equipo u otro personaje, se crean los mov
      }
      else if(this->getPrimerMovimiento())
      {

          this->cambiarAtaque(this->getVida());//para que siempre tenga el ataque igual a la vida

          this->actualizarMovimientos();//ya no se crea de nuevo la lista de mov, solamente se actualiza
      }
   return true;
}


