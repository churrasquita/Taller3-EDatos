#pragma once

#include "NodoBPlusBase.h"
#include "NodoGrafo.h"

class NodoBHoja:public NodoBPlusBase{
    private:
        NodoGrafo** datos;      
        NodoBHoja* siguiente_hoja;
    public:
        NodoBHoja(int orden);
        void insertar_en_hoja(int clave, NodoGrafo* nodo);
        bool esta_llena();
        NodoGrafo** get_datos();
        NodoBHoja* get_siguiente();
        void set_siguiente(NodoBHoja* siguiente);

        ~NodoBHoja();
};


