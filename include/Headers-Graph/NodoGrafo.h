#pragma once
class NodoGrafo{
    private:
        int id;
        int* padres;
        int cant_padres;
    public:
        NodoGrafo(int id);
        virtual bool es_directorio(); //verifica que sea directorio
        int* lista_padres();
        void agregar_padre(int padre);
        int get_id();
        virtual ~NodoGrafo();
};
