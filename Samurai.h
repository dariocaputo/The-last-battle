#ifndef SAMURAI_H_INCLUDED
#define SAMURAI_H_INCLUDED

#include "Tropa.h"

class Samurai : public Tropa
{

public:

    Samurai(ColorJugador unColor);
    ~Samurai();
    virtual void atacar(Tropa* objetivo);
    virtual void crearMovimientos();
    virtual void actualizarMovimientos();
     virtual bool crearOActualizar();

};

#endif // SAMURAI_H_INCLUDED
