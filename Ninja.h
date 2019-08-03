#ifndef NINJA_H_INCLUDED
#define NINJA_H_INCLUDED

#include "Tropa.h"
#include <time.h>

class Ninja : public Tropa
{

public:

    Ninja(ColorJugador unColor);
    ~Ninja();
    virtual void atacar(Tropa* objetivo);
    virtual void crearMovimientos();
    virtual void actualizarMovimientos();
     virtual bool crearOActualizar();

};

#endif // NINJA_H_INCLUDED
