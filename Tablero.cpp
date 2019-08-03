#include "Tablero.h"

Tablero::Tablero(int filas, int columnas)
{
    this->filas = filas;
    this->columnas = columnas;
    this->tablero = new ListaSE<ListaSE<Casillero*>*>();

    for (int i = 0; i < filas; i++)
    {
        this->nuevaFila = new ListaSE<Casillero*>();
        this->tablero->agregar(nuevaFila);

        for (int j = 0; j < columnas; j++)
        {
            Casillero* nuevaColumna = new Casillero(i, j);
            this->tablero->obtenerElemento(i)->agregar(nuevaColumna);
            //obtengo un elemento de la pos i de la lista tablero, y ese elemento es una lista nuevaFila que agregue antes
            //por eso le puedo decir->agregar(nuevaColumna);
        }
    }

}

Tablero::~Tablero()
{
    this->playerSpawnPoints->conocerCursor()->reiniciarCursor();
    while(this->playerSpawnPoints->conocerCursor()->avanzarCursor())
    {
        delete this->playerSpawnPoints->conocerCursor()->obtenerCursor();

    }
    delete this->playerSpawnPoints;


    this->nuevaFila->conocerCursor()->reiniciarCursor();
    while(this->nuevaFila->conocerCursor()->avanzarCursor())
    {
        delete this->nuevaFila->conocerCursor()->obtenerCursor();

    }
    delete this->nuevaFila;


    this->tablero->conocerCursor()->reiniciarCursor();
    while(this->tablero->conocerCursor()->avanzarCursor())
    {
        delete this->tablero->conocerCursor()->obtenerCursor();

    }
    delete this->tablero;
}

int Tablero::getCantFilas()
{
    return this->filas;
}

int Tablero::getCantColumnas()
{
    return this->columnas;
}

Casillero* Tablero::getCasillero(int posX, int posY)
{
    return this->tablero->obtenerElemento(posX)->obtenerElemento(posY);
}

void Tablero::imprimirTablero(int x, int y)
{
    system("cls");

    for (int i = 0; i < this->filas; i++)
    {
        std::cout << "\n";//espacio entre filas

        for (int j = 0; j < this->columnas; j++)
        {
           std::cout << " ";//espacio entre columnas

            if (this->getCasillero(j, i)->casilleroOcupado())//si el casillero está ocupado
            {

                       if (this->getCasillero(j, i)->getTropaOcupante()->getColor() == Rojo)
                       {
                             if(this->getCasillero(j,i) == this->getCasillero(x,y))//si es el mio que se pinte de rosado
                             {
                               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 13);
                               std::cout <<"[ "<<this->getCasillero(j, i)->getTropaOcupante()->getID()<<" ]";
                               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
                             }
                             else//sino de rojo fuerte
                             {
                                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
                                 std::cout <<"[ "<<this->getCasillero(j, i)->getTropaOcupante()->getID()<<" ]";
                                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
                             }

                        }
                        else//si es el equipo azul
                        {
                              if(this->getCasillero(j,i) == this->getCasillero(x,y))//si es el mio que se pinte de cyan
                             {
                               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 11);
                               std::cout <<"[ "<<this->getCasillero(j, i)->getTropaOcupante()->getID()<<" ]";
                               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
                             }
                             else//sino de azul
                             {
                                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                                 std::cout <<"[ "<<this->getCasillero(j, i)->getTropaOcupante()->getID()<<" ]";
                                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
                             }

                        }


            }
            else//desocupado
            {
                std::cout << "["<<this->getCasillero(j,i)->getPosX() <<","<< this->getCasillero(j,i)->getPosY()<<"]";//si está desocupado
            }
        }
        std::cout << "\n";
    }
}

void Tablero::generarPuntosDeSpawn()
{
    Casillero* casilleroDesocupado;
    this->playerSpawnPoints = new ListaSE<Casillero*>();

    for (int i = 0; i < this->filas; i++)
    {
        for (int j = 0; j < this->columnas; j++)
        {
            if (!this->getCasillero(j, i)->casilleroOcupado())//si el casillero está desocupado
            {
              casilleroDesocupado = this->getCasillero(j, i);
              this->playerSpawnPoints->agregar(casilleroDesocupado);//lo agrego a la lista de spawn

            }
        }
    }
}

void Tablero::inicializarTablero(Jugador* jugadorElegido)
{
  Tropa* tropaElegida;
  int t = 0;
  int rnd;

 while(t < this->getCantFilas())//o getCantColumnas ya que tienen igual dimension
 {
    tropaElegida = jugadorElegido->obtenerTropa(t);

     srand(time(NULL));
    do
    {
        rnd = rand() % this->playerSpawnPoints->contarElementos();

    }while(this->playerSpawnPoints->obtenerElemento(rnd)->casilleroOcupado());//mientras este ocupado el casillero sigue tirando randoms hasta encontrar uno libre

    this->playerSpawnPoints->obtenerElemento(rnd)->setOcupante(tropaElegida);//coloca la tropa en el casillero

    tropaElegida->setPosX(this->playerSpawnPoints->obtenerElemento(rnd)->getPosX());//actualiza la posicion de la tropa
    tropaElegida->setPosY(this->playerSpawnPoints->obtenerElemento(rnd)->getPosY());

    t++;
 }
}

bool Tablero::mover(Tropa* tropaElegida,bool primerMovimiento,int movPermitidos,int totalMovimientos)
{
   int playerPosX, playerPosY,x,y;
   bool eligio = false;
   std::string respuesta;
   playerPosX = tropaElegida->getPosX();
   playerPosY = tropaElegida->getPosY();

  if(movPermitidos > 0 && primerMovimiento)
  {
      while(eligio == false)
      {
          std::cout << "\nA que casillero de estos desea moverse?"<<std::endl;
          std::cout << "\nIngrese fila:"<<std::endl;
          std::cin>> x;
          std::cout << "\nIngrese columna:"<<std::endl;
          std::cin>> y;

          eligio = this->evaluarCasillero(tropaElegida,x,y);

          if(eligio == false)
          {
             SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
             std::cout << "\nEse movimiento no es posible!!!"<<std::endl;
             SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
             PlaySound(TEXT("fail.wav"), NULL, SND_SYNC);
             Sleep(1000);
            return false;//para que se refresque la pantalla
          }
      }

    this->tablero->obtenerElemento(playerPosX)->obtenerElemento(playerPosY)->desocupar();//borra el casillero ocupado actualmente
    tropaElegida->setPosX(x);
    tropaElegida->setPosY(y);
    this->tablero->obtenerElemento(x)->obtenerElemento(y)->setOcupante(tropaElegida);

   return true;
  }
  else
  {
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
         std::cout << "\nLa tropa ataca desde donde esta\n"<<std::endl;
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);

     system("pause");

     return true;
  }
  return false;
}

int Tablero::movPermitidos(Tropa* tropaElegida,int total)
{
      std::cout << "\nMovimientos permitidos:"<<std::endl;
      Casillero* movimiento;
      int i = 0;
      int movHabilitados = 0;
      bool permitido;

      while(i < total)
      {
         movimiento = tropaElegida->obtenerMovimiento(i);
         permitido = this->evaluarCasillero(movimiento);

         if(permitido)
         {
             movHabilitados++;
             movimiento->imprimirPos();//imprime todos los mov permitidos
         }
         i++;
      }

     if(movHabilitados==0)
     {
         std::cout<<"Ninguno"<<std::endl;
     }

     return movHabilitados;
}


bool Tablero::evaluarCasillero(Casillero* miCasillero)
{
   Casillero* casillero;
   int x,y;
   x = miCasillero->getPosX();
   y = miCasillero->getPosY();

    this->playerSpawnPoints->conocerCursor()->reiniciarCursor();
    while(this->playerSpawnPoints->conocerCursor()->avanzarCursor())
    {
          casillero = this->playerSpawnPoints->conocerCursor()->obtenerCursor();

          if(!casillero->casilleroOcupado() && x == casillero->getPosX() && y == casillero->getPosY())
          {
            if(casillero->getPosX()<this->getCantColumnas() && casillero->getPosX()>=0 && casillero->getPosY()<this->getCantFilas() && casillero->getPosY()>=0)
            {
               return true;//devuelve true y sale de la función
            }
          }
    }
    return false;
}

bool Tablero::evaluarCasillero(Tropa* tropaElegida,int x, int y)
{
   Casillero* casillero;
   bool ok;

    ok = tropaElegida->evaluarMiMovimiento(x,y);

   if(ok)//si esta dentro de los mov de la tropa, se chequea si en spawnpoints ese casillero esta vacio
   {     //y si no esta fuera de rango
        this->playerSpawnPoints->conocerCursor()->reiniciarCursor();
        while(this->playerSpawnPoints->conocerCursor()->avanzarCursor())
        {
              casillero = this->playerSpawnPoints->conocerCursor()->obtenerCursor();

              if(!casillero->casilleroOcupado() && x == casillero->getPosX() && y == casillero->getPosY())
              {
                if(casillero->getPosX()<this->getCantColumnas() && casillero->getPosX()>=0 && casillero->getPosY()<this->getCantFilas() && casillero->getPosY()>=0)
                {
                   return true;//devuelve true y sale de la función
                }
              }
        }
   }
   else
   {
      return false;
   }

   return false;//por defecto retorna false
}

void Tablero::buscarYDestruir(Tropa* tropaElegida)
{
      Casillero* casillero;
      int x, y, vision, cont = 0;

      x = tropaElegida->getPosX();
      y = tropaElegida->getPosY();//mi pos actual

      vision = tropaElegida->getVision();

    this->playerSpawnPoints->conocerCursor()->reiniciarCursor();
    while(this->playerSpawnPoints->conocerCursor()->avanzarCursor())
    {
        casillero = this->playerSpawnPoints->conocerCursor()->obtenerCursor();
        if(casillero->casilleroOcupado() && casillero->getTropaOcupante()->getPosX() == tropaElegida->getPosX() && casillero->getTropaOcupante()->getPosY() == tropaElegida->getPosY())
        {
            for (int i = y-vision; i <= y+vision; i++)
            {
                for (int j = x-vision; j <= x+vision; j++)
                {
                        if (i>=0 && i<this->getCantFilas() && j>=0 && j<this->getCantColumnas())//chequeo que no sea una pos fuera de rango
                        {
                              if(this->getCasillero(j,i) != this->getCasillero(x,y))//si el casillero es distinto al mio(para que no me busque a mí mismo)
                              {
                                   if(this->getCasillero(j,i)->casilleroOcupado() && this->getCasillero(j,i)->getTropaOcupante()->getColor() != tropaElegida->getColor())
                                   {
                                        cont++;
                                        this->combate(tropaElegida,this->getCasillero(j,i)->getTropaOcupante(), i, j); //se produce el combate (se ataca todos los enemigos vecinos)
                                        if(tropaElegida->getVida() <=0)
                                        {
                                              SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                                              std::cout<<"\nFin de la batalla\n"<<std::endl;
                                              SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
                                              return;//si muere nuestro enano atacante, la funcion termina, para que no siga atacando
                                        }

                                   }
                              }

                        }
                }
            }
        }
    }

    if(cont == 0)
    {
        std::cout<<"\n-------------------------------------"<<std::endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        std::cout << "\nNo hay enemigos a la vista\n" << std::endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        std::cout<<"\nFin de la batalla\n"<<std::endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
    }
}

void Tablero::combate(Tropa* tropaAtacante, Tropa* tropaVictima,int i,int j)
{
    std::cout<<"\n-------------------------------------"<<std::endl;
    std::cout<<"Tu " <<tropaAtacante->getNombre() <<" ataca a "<< tropaVictima->getNombre() <<" de la posicion:"<<std::endl;
    this->getCasillero(j,i)->imprimirPos();//es el casillero enemigo al cual puede atacar
    std::cout<<"Pega con un poder de "<< tropaAtacante->getAtaque()<<" puntos"<<std::endl;
    tropaAtacante->atacar(tropaVictima);

    if(tropaVictima->getVida()>0)
    {
         std::cout<<"El " <<tropaVictima->getNombre()<<" enemigo queda con "<<tropaVictima->getVida()<<" de vida"<<std::endl;
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cout<< tropaVictima->getNombre()<<" HA MUERTO..." <<std::endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
        PlaySound(TEXT("muerte1.wav"), NULL, SND_SYNC);
        this->getCasillero(j,i)->desocupar();

    }

    if(tropaAtacante->getVida() <= 0)
    {


        int miX = tropaAtacante->getPosX();
        int miY = tropaAtacante->getPosY();
        this->getCasillero(miX,miY)->desocupar();//se desocupa mi casillero

    }

}
