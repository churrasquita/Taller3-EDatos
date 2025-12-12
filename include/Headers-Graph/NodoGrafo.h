#pragma once

class NodoGrafo{
    private:
        int id;
        int* padres;
        struct NodoPadre {
            int id_padre;
            NodoPadre* next;
        };
        NodoPadre* cabeza;
    public:
        NodoGrafo(int id);
        virtual bool es_directorio(); //verifica que sea directorio
        int* lista_padres();
        void agregar_padre(int padre);
        int get_id();
        virtual ~NodoGrafo();
};


