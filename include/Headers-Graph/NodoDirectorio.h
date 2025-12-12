#pragma once
#include "NodoGrafo.h"

class NodoDirectorio:public NodoGrafo{
    public:
        NodoDirectorio(int id);
        ~NodoDirectorio();
        bool es_directorio();  
        int* lista_hijos();
};

