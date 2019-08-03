#include "Jugador.h"

Jugador::Jugador(std::string unNombre)
{
   this->nombre = unNombre;
   this->miTropa = new ListaSE<Tropa*>;
}

Jugador::~Jugador()
{
    this->miTropa->conocerCursor()->reiniciarCursor();
    while(this->miTropa->conocerCursor()->avanzarCursor())
    {
        delete this->miTropa->conocerCursor()->obtenerCursor();//borra las tropas elegidas

    }
    delete this->miTropa;//borra la lista

}

std::string Jugador::getNombre()
{
    return this->nombre;
}

void Jugador::sorteo(int numero)
{
        switch(numero)
        {
            case 0:
                 std::cout<<"Salio Ninja"<<std::endl;
              break;

            case 1:
                std::cout<<"Salio Contendiente"<<std::endl;
              break;

            case 2:
                std::cout<<"Salio Enano"<<std::endl;
              break;

            case 3:
                std::cout<<"Salio Samurai"<<std::endl;
              break;

            case 4:
                std::cout<<"Salio Arquero"<<std::endl;
              break;

            case 5:
                std::cout<<"Salio Knight"<<std::endl;
              break;
        }
}

int Jugador::eleccion(int numero,int& contador, ColorJugador unColor)
{
   std::string respuesta;

          if(numero == 0)
          {
             std::cout<<"Desea agregar al 'NINJA' (s/n)?"<<std::endl;
             std::cin>>respuesta;
             if(respuesta == "s")
             {
                PlaySound(TEXT("crearunidad.wav"), NULL, SND_SYNC);
                this->miTropa->agregar(new Ninja(unColor));
                contador++;
             }
          }
          else if(numero == 1)
          {
                std::cout<<"Desea agregar al 'CONTENDIENTE' (s/n)?"<<std::endl;
                std::cin>>respuesta;
                if(respuesta == "s")
                {
                     PlaySound(TEXT("crearunidad.wav"), NULL, SND_SYNC);
                    this->miTropa->agregar(new Contendiente(unColor));
                    contador++;
                }
          }
          else if(numero == 2)
          {
                std::cout<<"Desea agregar al 'ENANO' (s/n)?"<<std::endl;
                std::cin>>respuesta;
                if(respuesta == "s")
                {
                     PlaySound(TEXT("crearunidad.wav"), NULL, SND_SYNC);
                    this->miTropa->agregar(new Enano(unColor));
                    contador++;
                }
          }
          else if(numero == 3)
          {
                std::cout<<"Desea agregar al 'SAMURAI' (s/n)?"<<std::endl;
                std::cin>>respuesta;
                if(respuesta == "s")
                {
                     PlaySound(TEXT("crearunidad.wav"), NULL, SND_SYNC);
                    this->miTropa->agregar(new Samurai(unColor));
                    contador++;
                }
          }
          else if(numero == 4)
          {
                std::cout<<"Desea agregar al 'ARQUERO' (s/n)?"<<std::endl;
                std::cin>>respuesta;
                if(respuesta == "s")
                {
                     PlaySound(TEXT("crearunidad.wav"), NULL, SND_SYNC);
                    this->miTropa->agregar(new Arquero(unColor));
                    contador++;
                }
          }
          else if(numero == 5)
          {
                std::cout<<"Desea agregar al 'KNIGHT' (s/n)?"<<std::endl;
                std::cin>>respuesta;
                if(respuesta == "s")
                {
                      PlaySound(TEXT("crearunidad.wav"), NULL, SND_SYNC);
                    this->miTropa->agregar(new Knight(unColor));
                    contador++;
                }
          }

  return contador;
}


void Jugador::reclutarTropas(int n, ColorJugador unColor)
{
   int contador, sorteo1,sorteo2;
   int resultado;
   contador = 0;//inicio con en cero


    do
    {
         srand(time(NULL));//reinicia la semilla
        sorteo1 = rand()%6;//elige entre 0 y 5
        sorteo2 = rand()%6;//hay 6 tipos de tropas(arq,nin,ena,sam,con,knight)

        while(sorteo2 == sorteo1)
        {
             sorteo2 = rand()%6;
        }

         this->sorteo(sorteo1);
         this->sorteo(sorteo2);

         resultado = this->eleccion(sorteo1,contador,unColor);
         //a contador lo paso por ref, entonces el valor cambia y se ve reflejado afuera del método elección
          if(resultado == n)
          {
             return;//sale de la función
          }

          resultado = this->eleccion(sorteo2,contador,unColor);

          if(resultado == n)
          {
             return;//sale de la función
          }
      system("cls");
    }while(resultado < n);//lo hará mientras contador sea < n (dim del tablero)

}

Tropa* Jugador::seleccionarTropa(int rnd)
{
    Tropa* tropa;
    tropa = this->miTropa->obtenerElemento(rnd);
    return tropa;
}


int Jugador::totalTropas()
{
    int totalTropas;
    totalTropas = this->miTropa->contarElementos();
    return totalTropas;

}


Tropa* Jugador::obtenerTropa(int t)//elige una tropa en particular
{
    Tropa* tropa;
    tropa = this->miTropa->obtenerElemento(t);
    return tropa;
}


int Jugador::chequearTropaMuerta()
{
  int muertos= 0;
  Tropa* tropa;
    this->miTropa->conocerCursor()->reiniciarCursor();
    while(this->miTropa->conocerCursor()->avanzarCursor())
    {
        tropa=this->miTropa->conocerCursor()->obtenerCursor();
        if(tropa->getVida()<=0)
        {
           muertos++;
        }
    }
    return muertos;
}
