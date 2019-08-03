#ifndef KNIGHT_H_INCLUDED
#define KNIGHT_H_INCLUDED

#include "Tropa.h"

class Knight : public Tropa
{

public:

    Knight(ColorJugador unColor);
    ~Knight();
    virtual void atacar(Tropa* objetivo);
    virtual void crearMovimientos();
    virtual void actualizarMovimientos();
     virtual bool crearOActualizar();
};

#endif // KNIGHT_H_INCLUDED
