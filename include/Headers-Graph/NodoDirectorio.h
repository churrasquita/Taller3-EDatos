#pragma once
#include "NodoGrafo.h"

class NodoDirectorio:public NodoGrafo{
    private:
        struct NodoHijo {
            int id;
            NodoHijo* sig;
        };
        NodoHijo* lista;  // lista enlazada de hijos

    public:
        NodoDirectorio(int id);
        ~NodoDirectorio();
        bool es_directorio();  
        int* lista_hijos();
        void agregar_hijo(int id_hijo);
};

