#pragma once

class NodoBPlusBase {
    private:
        int* claves;     
        int orden;      
        bool es_hoja;  
        int num_claves; //cantidad de claves reales 
    public:
        NodoBPlusBase(int orden, bool esHoja);
        int* get_claves();
        int get_orden();
        bool es_Hoja();
        int get_num_claves();
        void set_num_claves(int cant_claves);
        ~NodoBPlusBase();
};
