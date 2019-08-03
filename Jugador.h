#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include "Tropa.h"

#include "Arquero.h"
#include "Ninja.h"
#include "Contendiente.h"
#include "Enano.h"
#include "Samurai.h"
#include "Knight.h"

#include <time.h>

#include <windows.h>//para sonido
#include <MMSystem.h>//para sonido


class Jugador
{

private:

    std::string nombre;
    ListaSE<Tropa*>* miTropa;//lista de tropas del jugador

public:

    Jugador(std::string unNombre);
    ~Jugador();
    std::string getNombre();
    int chequearTropaMuerta();
    void reclutarTropas(int n, ColorJugador unColor);
    Tropa* obtenerTropa(int t);
    Tropa* seleccionarTropa(int rnd);
    int totalTropas();

private:

    void sorteo(int numero);
    int eleccion(int numero, int& contador, ColorJugador unColor);

};

#endif // JUGADOR_H_INCLUDED
