#ifndef NODOS_H_INCLUDED
#define NODOS_H_INCLUDED

template<class T> class NodoS{

private:

    T dato;

    NodoS<T>* siguiente;

public:

    NodoS(const T& dato, NodoS<T>* puntero = NULL){

        this->dato = dato;
        this->siguiente = puntero;
    }

    T& obtenerDato(){

        return this->dato;
    }

    void cambiarDato(const T& nuevoDato){

        this->dato = nuevoDato;
    }

    NodoS<T>* obtenerSiguiente(){

        return this->siguiente;
    }

    void cambiarSiguiente(NodoS<T>* nuevoSiguiente){

        this->siguiente = nuevoSiguiente;
    }

};

#endif // NODOS_H_INCLUDED
