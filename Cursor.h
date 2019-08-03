#ifndef CURSOR_H_INCLUDED
#define CURSOR_H_INCLUDED

#include <stdexcept>
#include "NodoS.h"

template<class T> class Cursor
{

private:

    NodoS<T>* inicial;

    NodoS<T>* recorredor;

public:

    Cursor(NodoS<T>* puntero);

    bool avanzarCursor();

    T& obtenerCursor();

    void reiniciarCursor();

};

template<class T> Cursor<T>::Cursor(NodoS<T>* puntero)
{
    this->recorredor = NULL;
    this->inicial = puntero;
}

template<class T> bool Cursor<T>::avanzarCursor(){

    if(this->recorredor == NULL)
    {
        this->recorredor = this->inicial;
    }

    else
    {

        this->recorredor = this->recorredor->obtenerSiguiente();

    }

    return(this->recorredor != NULL);
}

template<class T> T& Cursor<T>::obtenerCursor()
{

    if(this->recorredor != NULL)
    {

        return this->recorredor->obtenerDato();
    }

    throw std::out_of_range("Puntero nulo");
}

template<class T> void Cursor<T>::reiniciarCursor(){

    this->recorredor = NULL;
}

#endif // CURSOR_H_INCLUDED
