#ifndef ENANO_H_INCLUDED
#define ENANO_H_INCLUDED

#include "Tropa.h"
#include <windows.h>//para el color de la letra

class Enano : public Tropa
{

public:

    Enano(ColorJugador unColor);
    ~Enano();
    virtual void atacar(Tropa* objetivo);
    virtual void crearMovimientos();
    virtual void actualizarMovimientos();
     virtual bool crearOActualizar();

};

#endif // ENANO_H_INCLUDED
