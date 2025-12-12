#pragma once
class NodoGrafo{
    private:
        int id;
    public:
        NodoGrafo(int id);
        bool es_directorio(); //verifica que sea directorio
        int* lista_padres();
        ~NodoGrafo(); 
};
