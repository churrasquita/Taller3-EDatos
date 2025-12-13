#pragma once
#include "NodoGrafo.h"

class NodoArchivo:public NodoGrafo {
    private:
        int tamaño;
        int tipo;
    public:
        NodoArchivo(int id, int tamaño, int tipo);
        bool es_directorio();
        int get_tamano(); 
        ~NodoArchivo();
};

