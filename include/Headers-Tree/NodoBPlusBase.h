#pragma once

class NodoBPlusBase {
    private:
        int* claves;     
        int orden;      
        bool es_hoja;  
    public:
        NodoBPlusBase(int orden, bool esHoja);
        ~NodoBPlusBase();
};
