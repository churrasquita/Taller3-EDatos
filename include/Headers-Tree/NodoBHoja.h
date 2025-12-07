#pragma once

#include "NodoBPlusBase.h"
#include "NodoGrafo.h"

class NodoBHoja:public NodoBPlusBase{
    private:
        NodoGrafo** datos;      
        NodoBHoja* siguienteHoja;
    public:
        NodoBHoja(int orden);
        ~NodoBHoja();
};


