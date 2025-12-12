#include "ArbolBPlus.h"
#include <iostream>
ArbolBPlus::ArbolBPlus(int orden){
    this->orden = orden;
    this->raiz = nullptr;
}
NodoGrafo* ArbolBPlus::buscar_nodo_grafo(int clave, int &accesos){
    accesos = 0;
    if(!raiz) return nullptr;
    NodoBPlusBase* nodo = raiz;
    while(!nodo->es_hoja()){
        accesos++;
        NodoBInterno* interno = (NodoBInterno*)nodo;
        int id= interno->buscar_siguiente(clave); //si es un nodo interno, se busca el siguiente para insertar
        nodo = interno->get_punteros()[id];
    }
    accesos++;
    // en caso de que no sea interno, es una hoja
    NodoBHoja* hoja = (NodoBHoja*)nodo;
    int n = hoja->get_num_claves();
    int* claves = hoja->get_claves();
    NodoGrafo** datos = hoja->get_datos();

    for(int i=0; i<n; i++){
        if(claves[i] == clave){
            return datos[i];
        }
    }
    return nullptr;
}

//método privado para buscar la hoja dentro de la estructura del árbol
NodoBHoja* ArbolBPlus::buscar_hoja(int clave, int &accesos){
    accesos = 0;
    if (!raiz) return nullptr;
    NodoBPlusBase* actual = raiz;
    while (actual && !actual->es_hoja()) {
        ++accesos;
        NodoBInterno* interno = (NodoBInterno*)actual;
        int id = interno->buscar_siguiente(clave);
        actual = interno->get_punteros()[id];
    }
    if (!actual) return nullptr;
    accesos++;
    return (NodoBHoja*)actual;
}
//método para poder hacer splits en las hojas al insertar los datos
void ArbolBPlus::split_hoja(NodoBHoja* hoja, int &clave_nueva, NodoBPlusBase* &nuevo_nodo){
    int n =hoja->get_num_claves();
    int mitad = n/2;
    NodoBHoja* nueva = new NodoBHoja(orden);

    //copiamos la parte superior
    for(int i=mitad, j = 0; i < n;i++,j++) {
        nueva->get_claves()[j] = hoja->get_claves()[i];
        nueva->get_datos()[j] = hoja->get_datos()[i];
        nueva->set_num_claves(nueva->get_num_claves()+1);
    }
    
    // cambiar
    hoja->set_num_claves(mitad);
    // se enlaza 
    nueva->set_siguiente(hoja->get_siguiente());
    hoja->set_siguiente(nueva);
    clave_nueva = nueva->get_claves()[0];
    nuevo_nodo = (NodoBPlusBase*) nueva;
}

//método para realizar split interno al insertar un dato
void ArbolBPlus::split_interno(NodoBInterno* interno, int &clave_nueva, NodoBPlusBase* &nuevo_nodo){
    int n = interno->get_num_claves();
    int mitad = n/2;
    NodoBInterno* nuevo = new NodoBInterno(orden);
    //itera sobre la parte superior del nodo interno
    for (int i = mitad+1, j=0; i< n;i++,j++) { 
        //j = es el nuevo nodo que está interno 
        nuevo->get_claves()[j] = interno->get_claves()[i];
        nuevo->get_punteros()[j] = interno->get_punteros()[i+1]; //movemos a la derehca

        nuevo->set_num_claves(nuevo->get_num_claves()+1); // se aumenta la cant de claves en 1
    }
    nuevo->get_punteros()[nuevo->get_num_claves()] = interno->get_punteros()[n+1] //puntero final
    clave_nueva = interno->get_claves()[mitad]; // es el padre

    interno->set_num_claves(mitad);
    nuevo_nodo = (NodoBPlusBase*) nuevo;
}

//inserta el NodoGrafo completo en la hoja del Árbol B+, usando la clave (ID) como índice.
void ArbolBPlus::insertar_nodo_grafo(int clave, NodoGrafo* nodo) {
    if (!raiz) {
        NodoBHoja* hoja = new NodoBHoja(orden);
        hoja->get_claves()[0] = clave;
        hoja->get_datos()[0] = nodo_grafo;
        hoja->set_num_claves(1);
        raiz = (NodoBPlusBase*)hoja; 
        return;
    }
    int accesos;

    NodoBHoja* hoja = buscar_hoja(clave, accesos); //buscamos si es que existe la hoja en el árbol 
    if (!hoja) {
        hoja = new NodoBHoja(orden);
        hoja->get_claves()[0] = clave;
        hoja->get_datos()[0] = nodo_grafo;
        hoja->set_num_claves(1);
        raiz = (NodoBPlusBase*) hoja;
        return;
    }

    hoja->insertar_en_hoja(clave, nodo_grafo);
    if (!hoja->esta_llena()) return;
    int clave_nueva;
    NodoBPlusBase* nuevo_n = nullptr;
    split_hoja(hoja, clave_nueva, nuevo_n);
    insertar_en_padre(hoja, clave_nueva, nuevo_n);
}

NodoBPlusBase* ArbolBPlus::buscar_padre_rec(NodoBPlusBase* actual, NodoBPlusBase* hijo){
    if (!actual || actual->es_hoja()) return nullptr;
    NodoBInterno* interno = (NodoBInterno*)actual;
    int n = interno->get_num_claves(); //variabla que guarda la cantidad de claves
    NodoBPlusBase** punteros = interno->get_punteros(); 
    for(int i= 0; i<=n;i++) {
        if (punteros[i] == hijo) return actual;
        NodoBPlusBase* padre= buscar_padre_rec(punteros[i], hijo);
        if (padre){
            return padre;
        }
    }
    return nullptr;
}

ArbolBPlus::~ArbolBPlus(){}