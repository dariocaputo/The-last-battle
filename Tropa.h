 #ifndef TROPA_H_INCLUDED
#define TROPA_H_INCLUDED

#include "Casillero.h"
#include "ListaSE.h"

class Casillero;

enum ColorJugador
{
    Rojo,
    Azul
};

class Tropa//Clase base
{

protected:

   std::string nombre,ID;
   int vida, ataque, vision, posX, posY;
   ColorJugador color;
   bool primerMovimiento, movio;
   ListaSE<Casillero*>* misMovimientos;

public:

    std::string getNombre();
     std::string getID();
    int getPosX();
    int getPosY();
    bool evaluarMiMovimiento(int x, int y);
    bool getMovio();
    void cambiarMovio();
    bool getPrimerMovimiento();
    void cambiarPrimerMovimiento();
    void cambiarAtaque(int nuevoAtaque);
    ColorJugador getColor();
    void setPosX(int nuevaPosX);
    void setPosY(int nuevaPosY);
    int getVida();
    int getAtaque();
    int getVision();
    void cambiarVision(int nuevaVision);
    void recibirDanio(int danio);
    int totalMovimientos();
    Casillero* obtenerMovimiento(int t);
    virtual void atacar(Tropa* objetivo) = 0;
    virtual void crearMovimientos() = 0;
    virtual void actualizarMovimientos() = 0;
    virtual bool crearOActualizar() = 0;

};

#endif // TROPA_H_INCLUDED
