#pragma once

#include "NodoBPlusBase.h"
#include "NodoBHoja.h"
#include "NodoBInterno.h"
#include "NodoGrafo.h"

class ArbolBPlus {
    private:
        NodoBPlusBase* raiz;
        int orden;
        NodoBHoja* buscar_hoja(int clave, int &accesos);
        void split_hoja(NodoBHoja* hoja, int &clave_nueva, NodoBPlusBase* &nuevo_nodo);
        void split_interno(NodoBInterno* interno, int &clave_nueva, NodoBPlusBase* &nuevo_nodo);
        NodoBPlusBase* buscar_padre_rec(NodoBPlusBase* actual, NodoBPlusBase* hijo);
        void insertar_en_padre(NodoBPlusBase* nodo, int clave, NodoBPlusBase* nuevo_hijo);
    public:
        ArbolBPlus(int orden);
        //se realizan en la clase ya que corresponde a datos que debería manejar dicha estructura, no acceder desde el main
        void insertar_nodo_grafo(int clave, NodoGrafo* nodo_grafo); 
        NodoGrafo* buscar_nodo_grafo(int clave, int &accesos);
        ~ArbolBPlus(); 
};

