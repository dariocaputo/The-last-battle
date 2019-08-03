#include "Enano.h"

Enano::Enano(ColorJugador unColor)
{
      this->nombre = "Enano";
      this->ID = "E";
      this->vida = 200;
      this->ataque = 100;
      this->vision = 1;
      this->movio = false;
      this->primerMovimiento = false;
      this->color = unColor;
      this->misMovimientos = new ListaSE<Casillero*>();
}

Enano::~Enano()
{
    this->misMovimientos->conocerCursor()->reiniciarCursor();
    while(this->misMovimientos->conocerCursor()->avanzarCursor())
    {
        delete this->misMovimientos->conocerCursor()->obtenerCursor();

    }
    delete this->misMovimientos;
}

void Enano::atacar(Tropa* objetivo)
{
   objetivo->recibirDanio(this->ataque);
   this->vida-=10;//pierde 10 pts de vida en cada ataque

       if(this->vida > 0)
       {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 11);
            std::cout<<"\nTu enano queda con: "<< this->getVida()<<" de vida" <<std::endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
       }
       else
       {
           PlaySound(TEXT("muerte1.wav"), NULL, SND_SYNC);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 11);
            std::cout<<"Tu enano MURIO..." <<std::endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
       }


}

void Enano::crearMovimientos()
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

void Enano::actualizarMovimientos()//actualiza todos los movimientos posibles que puede hacer la tropa,segun la pos actual
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

bool Enano::crearOActualizar()
{
       if(this->getPrimerMovimiento()==false && this->getMovio()==false)
       {
          this->crearMovimientos();
          this->cambiarPrimerMovimiento();
          this->cambiarMovio();
       }
       else if(this->getPrimerMovimiento() && this->getMovio())
       {
          this->cambiarMovio();//cambio solo el movio, para que en un turno mueva y al otro no
           return false;//retorna falso para que no se mueva la tropa
       }
       else if(this->getPrimerMovimiento() && this->getMovio()==false)
       {
            this->actualizarMovimientos();
            this->cambiarMovio();
            //el enano se mueve
            //no hace falta poner aca el return true porque lo hace al final esta funcion
       }
     return true;
}
