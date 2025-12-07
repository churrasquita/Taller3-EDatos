#pragma once
#include "NodoBPlusBase.h"

class NodoBInterno:public NodoBPlusBase {
    private:
        NodoBPlusBase** punteros;
        int buscar_siguiente();
    public:
        NodoBInterno(int orden);
        ~NodoBInterno();
};

