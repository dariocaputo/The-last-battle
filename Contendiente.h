#ifndef CONTENDIENTE_H_INCLUDED
#define CONTENDIENTE_H_INCLUDED

#include "Tropa.h"

class Contendiente : public Tropa
{

public:

    Contendiente(ColorJugador unColor);
    ~Contendiente();
    virtual void atacar(Tropa* objetivo);
    virtual void crearMovimientos();
    virtual void actualizarMovimientos();
     virtual bool crearOActualizar();

};

#endif // CONTENDIENTE_H_INCLUDED
