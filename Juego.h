#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "Jugador.h"
#include "Tablero.h"


class Juego
{
   private:
        Jugador* PJ1;
        Jugador* PJ2;
        Tablero* miTablero;

    public:
         Juego();
         ~Juego();
         void iniciar();

    private:
        Jugador* setJugador();
        bool jugar();
        bool determinarGanador(int tropasMuertasPJ1,int tropasMuertasPJ2);
        void turno(Jugador* jugador);
        void estadoTropa(Tropa* tropa,Jugador* jugador);//informa la vida, ataque, etc. de la tropa
};

#endif // JUEGO_H_INCLUDED
