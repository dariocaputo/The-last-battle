#include "Ninja.h"

Ninja::Ninja(ColorJugador unColor)
{
      this->nombre = "Ninja";
      this->ID = "N";
      this->vida = 100;
      this->ataque = 10;//por defecto es diez pero cambia cada vez que es elegido
      this->vision = 1;
      this->color = unColor;
      this->misMovimientos = new ListaSE<Casillero*>();
      this->primerMovimiento = false;
}

Ninja::~Ninja()
{
    this->misMovimientos->conocerCursor()->reiniciarCursor();
    while(this->misMovimientos->conocerCursor()->avanzarCursor())
    {
        delete this->misMovimientos->conocerCursor()->obtenerCursor();

    }
    delete this->misMovimientos;
}

void Ninja::atacar(Tropa* objetivo)
{
     objetivo->recibirDanio(this->ataque);

}

void Ninja::crearMovimientos()
{
    int x,y;
    x = this->getPosX();
    y = this->getPosY();

    this->misMovimientos->agregar(new Casillero(x-1,y-1));//ARRIBA IZQ
    this->misMovimientos->agregar(new Casillero(x+1,y-1));//ARRIBA DER
    this->misMovimientos->agregar(new Casillero(x-1,y+1));//ABAJO IZQ
    this->misMovimientos->agregar(new Casillero(x+1,y+1));//ABAJO DER
}

void Ninja::actualizarMovimientos()//actualiza todos los movimientos posibles que puede hacer la tropa,segun la pos actual
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
         casillero->setNuevaPos(x-1,y-1);//ARRIBA IZQ
       }
       else if(pos == 1)
       {
         casillero->setNuevaPos(x+1,y-1);//ARRIBA DER
       }
       else if(pos == 2)
       {
         casillero->setNuevaPos(x-1,y+1);//ABAJO IZQ
       }
       else if(pos == 3)
       {
         casillero->setNuevaPos(x+1,y+1);//ABAJO DER
       }

        pos++;

    }

}

bool Ninja::crearOActualizar()
{
      if(this->getPrimerMovimiento()==false)
      {
          this->crearMovimientos();//se crea la lista con todas las coordenadas
          this->cambiarPrimerMovimiento();//de esta forma al elegir a otro arquero del mismo equipo u otro personaje, se crean los mov
      }
      else if(this->getPrimerMovimiento())
      {

               int rnd;
               srand(time(NULL));//pone la semilla en cero
               rnd = rand()% 11;//entre 0 y 10
               this->cambiarAtaque(rnd*10);//da entre 0 y cien, o sea puede tocarle 0 y ataca sin fuerza.


          this->actualizarMovimientos();//ya no se crea de nuevo la lista de mov, solamente se actualiza
      }
   return true;
}


