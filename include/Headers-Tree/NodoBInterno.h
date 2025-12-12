#pragma once
#include "NodoBPlusBase.h"

class NodoBInterno:public NodoBPlusBase {
    private:
        NodoBPlusBase** punteros;
    public:
        NodoBInterno(int orden);
        NodoBPlusBase** get_punteros();
        int buscar_siguiente(int clave);
        ~NodoBInterno();
};

