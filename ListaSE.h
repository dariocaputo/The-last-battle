#ifndef LISTASE_H_INCLUDED
#define LISTASE_H_INCLUDED

#include "Cursor.h"

template<class T> class ListaSE{

private:

    NodoS<T>* primero;

    NodoS<T>* ultimo;

    unsigned int tamanio;

    Cursor<T>* cursor;

public:

    ListaSE();

    ListaSE(const ListaSE<T>& otraLista);

    ~ListaSE();

    bool estaVacia() const;

    unsigned int contarElementos() const;

    void agregar(const T& elemento);

    void agregar(const T& elemento, unsigned int posicion);

    void remover(unsigned int posicion);

    unsigned int esta(const T& elemento) const;

    T& obtenerElemento(unsigned int posicion) const;

    T& operator[](int pos) const;

    void asignar(const T& elemento, unsigned int posicion);

    bool operator== (const ListaSE<T>& otraLista) const;

    Cursor<T>* conocerCursor() const;

private:

    NodoS<T>* obtenerNodo(unsigned int posicion) const;

};

//PÚBLICO

template<class T> ListaSE<T>::ListaSE(){

    this->primero = NULL;
    this->ultimo = NULL;
    this->tamanio = 0;
    this->cursor = new Cursor<T>(this->primero);
}

template<class T> ListaSE<T>::ListaSE(const ListaSE<T>& otraLista){

    this->primero = NULL;

    this->ultimo = NULL;

    this->tamanio = 0;

    this->cursor = new Cursor<T>(this->primero);

    Cursor<T>* cursorOtraLista = otraLista.conocerCursor();

    cursorOtraLista->reiniciarCursor();

    while(cursorOtraLista->avanzarCursor()){

        this->agregar(cursorOtraLista->obtenerCursor());
    }

}

template<class T> ListaSE<T>::~ListaSE(){

    while(this->tamanio > 0){

        this->remover(0);
    }

    delete cursor;
}

template<class T> bool ListaSE<T>::estaVacia() const{

    return (this->tamanio == 0);
}

template<class T> unsigned int ListaSE<T>::contarElementos() const{

    return this->tamanio;
}

template<class T> void ListaSE<T>::agregar(const T& elemento){

    this->agregar(elemento, this->tamanio);
}

template<class T> void ListaSE<T>::agregar(const T& elemento, unsigned int posicion){

    if(posicion <= this->tamanio){

        NodoS<T>* nodoNuevo = new NodoS<T>(elemento);

        if(posicion == 0){

            nodoNuevo->cambiarSiguiente(this->primero);
            this->primero = nodoNuevo;
            delete this->cursor;
            this->cursor = new Cursor<T>(this->primero);

            if(tamanio == 0){
                this->ultimo = nodoNuevo;
            }
        }

        else if (posicion != tamanio){

            NodoS<T>* nodoAnterior = this->obtenerNodo(posicion - 1);
            nodoNuevo->cambiarSiguiente(nodoAnterior->obtenerSiguiente());
            nodoAnterior->cambiarSiguiente(nodoNuevo);
        }

        else{

            this->ultimo->cambiarSiguiente(nodoNuevo);
            this->ultimo = nodoNuevo;
        }

        this->tamanio++;
    }
}

template<class T> void ListaSE<T>::remover(unsigned int posicion){

    if(posicion < this->tamanio){

        NodoS<T>* nodoEliminar;

        if(posicion == 0){

            nodoEliminar = this->primero;
            this->primero = nodoEliminar->obtenerSiguiente();
            delete this->cursor;
            this->cursor = new Cursor<T>(this->primero);
        }

        else if(posicion < tamanio-1){

            NodoS<T>* nodoAnterior = this->obtenerNodo(posicion - 1);
            nodoEliminar = nodoAnterior->obtenerSiguiente();
            nodoAnterior->cambiarSiguiente(nodoEliminar->obtenerSiguiente());
        }

        else{

            NodoS<T>* nodoAnterior = this->obtenerNodo(posicion - 1);
            nodoEliminar = nodoAnterior->obtenerSiguiente();
            nodoAnterior->cambiarSiguiente(nodoEliminar->obtenerSiguiente());
            this->ultimo = nodoAnterior;
        }

        delete nodoEliminar;

        this->tamanio--;
    }
}

template<class T> unsigned int ListaSE<T>::esta(const T& elemento) const{

    this->cursor->reiniciarCursor();

    unsigned int i = 0;

    while(this->cursor->avanzarCursor()){

        if(this->cursor->obtenerCursor() == elemento){

            return i;
        }

        i++;
    }

    return (-1);
}

template<class T> T& ListaSE<T>::obtenerElemento(unsigned int posicion) const
{

    if(posicion < this->tamanio)
    {
        return this->obtenerNodo(posicion)->obtenerDato();
    }

    throw std::invalid_argument("Fuera de Rango");
}

template<class T> T& ListaSE<T>::operator[](int pos) const{

    return this->obtenerElemento(pos);
}

template<class T> void ListaSE<T>::asignar(const T& elemento, unsigned int posicion){

    if(posicion < this->tamanio){

        this->obtenerNodo(posicion)->cambiarDato(elemento);
    }

}

template<class T> bool ListaSE<T>::operator== (const ListaSE<T>& otraLista) const{

    if(this->tamanio == otraLista.tamanio){

        Cursor<T>* cursorOtraLista = otraLista.conocerCursor();

        cursorOtraLista->reiniciarCursor();

        this->cursor->reiniciarCursor();

        while(this->cursor->avanzarCursor() && cursorOtraLista->avanzarCursor()){

            if(this->cursor->obtenerCursor() != cursorOtraLista->obtenerCursor()){

                return false;
            }
        }

        return true;
    }

    return false;
}

template<class T> Cursor<T>* ListaSE<T>::conocerCursor() const{

    return this->cursor;
}


//PRIVADO

template<class T> NodoS<T>* ListaSE<T>::obtenerNodo(unsigned int posicion) const{

    NodoS<T>* punteroActual = this->primero;

    for(unsigned int i = 0; i < posicion; i++){

        punteroActual = punteroActual->obtenerSiguiente();
    }

    return punteroActual;
}

#endif // LISTASE_H_INCLUDED
