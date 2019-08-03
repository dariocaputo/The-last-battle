#include "Juego.h"

Juego::Juego()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 14);//el primero es el color de fondo y el otro el de la letra
    std::cout << "***The Last Battle***" << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);

     int dim;
     std::cout << "\nElija el tamaño del mapa:"<<std::endl;
       std::cout << "6 (pequeño)"<<std::endl;
        std::cout << "8 (mediano)"<<std::endl;
         std::cout << "10 (grande)"<<std::endl;

     std::cin >> dim;

     while(dim!=6 && dim!=8 && dim!=10)
     {
        system("cls");

         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cout << "Solo puede elegir 6, 8 o 10!!! Reingrese..."<<std::endl;
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
        PlaySound(TEXT("fail.wav"), NULL, SND_SYNC);
        std::cin >> dim;
     }

     this->miTablero = new Tablero(dim,dim);

     this->miTablero->generarPuntosDeSpawn();//genera puntos de spawn
     system("cls");
     std::cout << "Set PJ1" <<std::endl;
     this->PJ1 = this->setJugador();
     this->PJ1->reclutarTropas(dim,Rojo);//llena la lista de tropas del jugador
     this->miTablero->inicializarTablero(PJ1);//coloca las tropas de pj1 en el tablero
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 14);
     std::cout << "\nColocando tropas en el tablero..." <<std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
     Sleep(3000);
     system("cls");
     std::cout << "Set PJ2" <<std::endl;
     this->PJ2 = this->setJugador();
     this->PJ2->reclutarTropas(dim,Azul);
     this->miTablero->inicializarTablero(PJ2);//coloca las tropas de pj2 en el tablero
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 14);
     std::cout << "\nColocando tropas en el tablero..." <<std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
      Sleep(3000);
     system("cls");
}

Juego::~Juego()
{
    delete this->PJ1;
    delete this->PJ2;
    delete this->miTablero;
}

void Juego::iniciar()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 14);
    std::cout << "Cargando...\n" << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
    Sleep(3000);

    bool hayGanador = false;

     while(hayGanador == false)
     {
         hayGanador = this->jugar();
     }

     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 14);//AMARILLO
     std::cout << "FIN DEL JUEGO"<<std::endl;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);

}

bool Juego::determinarGanador(int tropasMuertasPJ1, int tropasMuertasPJ2)
{
      int totalTropasPJ1 = 0, totalTropasPJ2 = 0;

      totalTropasPJ1 = this->PJ1->totalTropas();
      totalTropasPJ2 = this->PJ2->totalTropas();

       if((totalTropasPJ2 == tropasMuertasPJ2) && (totalTropasPJ1 == tropasMuertasPJ1))
       {
 //Si el atacante es un enano que tiene 10 de vida y es el último en pie, (y el enemigo también es el ultimo y tiene poca vida)
 //si tu enano lo ataca, quiza ambos mueran, y en ese caso los dos jugadores se quedaran sin tropas. Entonces hay empate.
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 14);//AMARILLO
            std::cout << "Ambos jugadores se quedaron sin tropas. Hay empate!!!" << std::endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
            PlaySound(TEXT("empate.wav"), NULL, SND_SYNC);
             return true;
       }
       else if(totalTropasPJ2 == tropasMuertasPJ2)
       {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 14);//AMARILLO
            std::cout << "\nEl PJ1 " <<this->PJ1->getNombre() <<" es el ganador!!!" << std::endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
            PlaySound(TEXT("victoria.wav"), NULL, SND_SYNC);
            return true;   //return true y se termina el juego
       }
       else if(totalTropasPJ1 == tropasMuertasPJ1)
       {
          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 14);//AMARILLO
          std::cout << "\nEl PJ2 " <<this->PJ2->getNombre() <<" es el ganador!!!" << std::endl;
          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
          PlaySound(TEXT("victoria.wav"), NULL, SND_SYNC);
          return true; //return true y se termina el juego
       }

   return false;
}


bool Juego::jugar()
{
       int tropasMuertasPJ1 = 0 , tropasMuertasPJ2 = 0;
       bool fin;

        this->turno(PJ1);//ataca pj1

        tropasMuertasPJ1 = this->PJ1->chequearTropaMuerta();
        tropasMuertasPJ2 = this->PJ2->chequearTropaMuerta();

         fin = this->determinarGanador(tropasMuertasPJ1,tropasMuertasPJ2);
         if(fin)
         {
             return true;
         }

        tropasMuertasPJ1 = 0;
        tropasMuertasPJ2 = 0;

        this->turno(PJ2);//ataca pj2

        tropasMuertasPJ1 = this->PJ1->chequearTropaMuerta();
        tropasMuertasPJ2 = this->PJ2->chequearTropaMuerta();

        fin = this->determinarGanador(tropasMuertasPJ1,tropasMuertasPJ2);
        if(fin)
        {
             return true;
        }

    return false;
}


Jugador* Juego::setJugador()
{
      std::string nombreJugador;
      std::cout << "Ingrese su nombre: ";
      std::cin >> nombreJugador;
      system("cls");
     return (new Jugador(nombreJugador));
}


void Juego::turno(Jugador* jugador)
{
    Tropa* tropa;
    int totalMovimientos, rnd, movPermitidos = 0;
    bool primerMovimiento, verdadero;

    srand(time(NULL));//al poner esto acá, la eleccion de tropa se hace mucho mas rápido, cuando quedan pocos jugadores
       do
       {

          rnd = rand() % jugador->totalTropas();
          tropa = jugador->seleccionarTropa(rnd);//se elige al azar una de las tropas que esté viva
       }while(tropa->getVida()<=0);

        primerMovimiento = tropa->crearOActualizar();//la tropa crea su lista de mov por primera vez, o solo la actualiza según su pos actual

      do
      {
         this->miTablero->imprimirTablero(tropa->getPosX(),tropa->getPosY());
         this->estadoTropa(tropa,jugador);//imprime el estado de la tropa elegida

          if(primerMovimiento)
          {
             totalMovimientos = tropa->totalMovimientos();//devuelve total de movimientos de la tropa
             movPermitidos = this->miTablero->movPermitidos(tropa,totalMovimientos);
             //el tablero devuelve de la cant. total de movimientos, solo la cant de permitidos
          }

            verdadero = this->miTablero->mover(tropa,primerMovimiento,movPermitidos,totalMovimientos);//mueve la tropa
      }while(verdadero==false);

        this->miTablero->imprimirTablero(tropa->getPosX(),tropa->getPosY());
       this->miTablero->buscarYDestruir(tropa);//la tropa ve a los enemigos vecinos y ataca a todos
       system("pause");
}

void Juego::estadoTropa(Tropa* tropa,Jugador* jugador)
{
     std::cout<<"\n-------------------------------------"<<std::endl;

        if(jugador == this->PJ1)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 14);//AMARILLO
            std::cout<<"TURNO del PJ1 "<<jugador->getNombre()<<std::endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
        }
        else
        {
             SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 14);//AMARILLO
             std::cout<<"TURNO del PJ2 "<<jugador->getNombre()<<std::endl;
             SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
        }

    std::cout << "\nTropa elegida: " << tropa->getNombre() << std::endl;
    std::cout << "Posicion: [" <<tropa->getPosX()<<","<<tropa->getPosY()<<"]"<<std::endl;
    std::cout << "Vida: " << tropa->getVida() << std::endl;
    std::cout << "Poder de ataque: " << tropa->getAtaque() << std::endl;
    std::cout << "Vision: " << tropa->getVision() << std::endl;
    if(tropa->getColor() == 0)
    {
        std::cout << "Color de bandera:"<< std::endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cout << "Rojo"<< std::endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
    }
    else
    {
        std::cout << "Color de bandera:"<< std::endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        std::cout << "Azul"<< std::endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
    }
        std::cout<<"-------------------------------------"<<std::endl;
}
