#ifndef ARQUERO_H_INCLUDED
#define ARQUERO_H_INCLUDED

#include "Tropa.h"
#include <time.h>

class Arquero : public Tropa
{

public:

    Arquero(ColorJugador unColor);
    ~Arquero();
    virtual void atacar(Tropa* objetivo);
    virtual void crearMovimientos();
    virtual void actualizarMovimientos();
    virtual bool crearOActualizar();
};

#endif // ARQUERO_H_INCLUDED
