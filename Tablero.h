#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

#include "Jugador.h"
#include "Casillero.h"

class Tablero
{

private:

    int filas;
    int columnas;
    ListaSE<ListaSE<Casillero*>*>* tablero;//tablero es un puntero a una lista DE una lista de casilleros
    ListaSE<Casillero*>* nuevaFila;
    ListaSE<Casillero*>* playerSpawnPoints;

public:

    Tablero(int filas, int columnas);
    ~Tablero();
    void inicializarTablero(Jugador* jugadorElegido);
    bool mover(Tropa* tropaElegida,bool primerMovimiento,int movPermitidos,int totalMovimientos);//se encarga de mover al jugador de un casillero a otro
    int movPermitidos(Tropa* tropaElegida,int total);//devuelve el total de cas posibles a los cuales la tropa puede moverse
    void imprimirTablero(int x, int y);
    void generarPuntosDeSpawn();
    void buscarYDestruir(Tropa* tropaElegida);//busca un enemigo vecino, y lo ataca

private: //para usar solo dentro de tablero.cpp

    Casillero* getCasillero(int posX, int posY);
    int getCantFilas();
    int getCantColumnas();
    bool evaluarCasillero(Casillero* miCasillero);//evalua si el casillero es apto para ocuparlo
    bool evaluarCasillero(Tropa* tropaElegida,int x, int y);//evalua si el casillero esta libre en "playerspawnpoints" y si esta dentro de la lista "misMovimientos" de la tropa
    void combate(Tropa* tropaAtacante, Tropa* tropaVictima,int i,int j);//se genera el combate entre dos tropas que se encuentran

};

#endif // TABLERO_H_INCLUDED
