#include "Arquero.h"

Arquero::Arquero(ColorJugador unColor)
{
      this->nombre = "Arquero";
      this->ID = "A";
      this->vida = 60;
      this->ataque = 50;
      this->vision = 1;//por defecto es uno, pero puede cambiar cada vez que es elegido
      this->color = unColor;
      this->misMovimientos = new ListaSE<Casillero*>();
      this->primerMovimiento = false;
}

Arquero::~Arquero()
{
    this->misMovimientos->conocerCursor()->reiniciarCursor();
    while(this->misMovimientos->conocerCursor()->avanzarCursor())
    {
        delete this->misMovimientos->conocerCursor()->obtenerCursor();
          //borra los new casillero que fui agregando a la lista
    }
    delete this->misMovimientos;//borra el new ListaSE
}

void Arquero::atacar(Tropa* objetivo)
{
     objetivo->recibirDanio(this->ataque);
     this->vida+=10;

}

void Arquero::crearMovimientos()
{
    int x,y;
    x = this->getPosX();
    y = this->getPosY();

    this->misMovimientos->agregar(new Casillero(x+1,y)); //DERECHA
    this->misMovimientos->agregar(new Casillero(x-1,y));//IZQUIERDA
    this->misMovimientos->agregar(new Casillero(x,y-1));//ARRIBA
    this->misMovimientos->agregar(new Casillero(x,y+1));//ABAJO
    this->misMovimientos->agregar(new Casillero(x-1,y-1));//ARRIBA IZQ
    this->misMovimientos->agregar(new Casillero(x+1,y-1));//ARRIBA DER
    this->misMovimientos->agregar(new Casillero(x-1,y+1));//ABAJO IZQ
    this->misMovimientos->agregar(new Casillero(x+1,y+1));//ABAJO DER
}

void Arquero::actualizarMovimientos()//actualiza todos los movimientos posibles que puede hacer la tropa,segun la pos actual
{
    int pos = 0;
    int x,y;
    x = this->getPosX();
    y = this->getPosY();
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
       else if(pos == 4)
       {
         casillero->setNuevaPos(x-1,y-1);//ARRIBA IZQ
       }
       else if(pos == 5)
       {
         casillero->setNuevaPos(x+1,y-1);//ARRIBA DER
       }
       else if(pos == 6)
       {
         casillero->setNuevaPos(x-1,y+1);//ABAJO IZQ
       }
       else if(pos == 7)
       {
         casillero->setNuevaPos(x+1,y+1);//ABAJO DER
       }

        pos++;

    }

}

bool Arquero::crearOActualizar()
{
      if(this->getPrimerMovimiento()==false)
      {
          this->crearMovimientos();//se crea la lista con todas las coordenadas
          this->cambiarPrimerMovimiento();//de esta forma al elegir a otro arquero del mismo equipo u otro personaje, se crean los mov
      }
      else if(this->getPrimerMovimiento())
      {
              int rnd;
              srand(time(NULL));//reinicia la semilla
               rnd=(1+(rand() % 100));//de 1 a 100
              //tambien puede escribirse 1+rand()% (101-1);

               if(rnd<=30)
               {
                  this->cambiarVision(1);//30%
               }
               else
               {
                  this->cambiarVision(2);//70%
               }


          this->actualizarMovimientos();//ya no se crea de nuevo la lista de mov, solamente se actualiza
      }

      return true;

}


