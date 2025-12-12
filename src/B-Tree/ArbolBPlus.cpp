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
    while(!nodo->es_Hoja()){
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
    while (actual && !actual->es_Hoja()) {
        accesos++;
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
    nuevo->get_punteros()[nuevo->get_num_claves()] = interno->get_punteros()[n+1];//puntero final
    clave_nueva = interno->get_claves()[mitad]; // es el padre

    interno->set_num_claves(mitad);
    nuevo_nodo = (NodoBPlusBase*) nuevo;
}

//inserta el NodoGrafo completo en la hoja del Árbol B+, usando la clave (ID) como índice.
void ArbolBPlus::insertar_nodo_grafo(int clave, NodoGrafo* nodo_grafo) {
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
    if (!actual || actual->es_Hoja()) return nullptr;
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

void ArbolBPlus::eliminar(int clave) {
    if (!raiz) return;
    int accesos = 0;
    NodoBHoja* hoja = buscar_hoja(clave,accesos);
    int* claves = hoja->get_claves();
    NodoGrafo** datos = hoja->get_datos();
    int n = hoja->get_num_claves();

    int pos = -1; //posición dentro del árbol
    for (int i = 0; i<n; i++){
        if (claves[i] == clave) {
            pos = i;
            break;
        }
    }
    if (pos == -1) return; // no existe

    // dezplazamos a la izquierda
    for(int i=pos; i <n-1; i++) {
        claves[i] = claves[i+1];
        datos[i] = datos[i+1];
    }
    // último queda vacío
    claves[n-1] = 0;
    datos[n-1] = nullptr;
    hoja->set_num_claves(n-1);
    // caso si es que la raíz queda vacía
    if (hoja==raiz && hoja->get_num_claves() == 0) {
        delete raiz;
        raiz = nullptr;
    }
}

void ArbolBPlus::insertar_en_padre(NodoBPlusBase* nodo,int clave, NodoBPlusBase* nuevo_hijo){
    //si es la raíz
    if (nodo==raiz){
        NodoBInterno* nueva_raiz = new NodoBInterno(orden);
        nueva_raiz->get_claves()[0] = clave;
        nueva_raiz->set_num_claves(1);
        nueva_raiz->get_punteros()[0] =nodo;
        nueva_raiz->get_punteros()[1] = nuevo_hijo;
        raiz = nueva_raiz;
        return;
    }
    // buscar el padre real
    NodoBPlusBase* padre = buscar_padre_rec(raiz, nodo);
    NodoBInterno* p = (NodoBInterno*)padre; //casting

    int* claves = p->get_claves();
    NodoBPlusBase** punteros = p->get_punteros();
    int n = p->get_num_claves();

    // insertar clave y nuevo_hijo en posición ordenada
    int i = 0;
    while(i<n && claves[i]<clave){
        i++;
    }

    for(int j=n; j>i;j--){
        claves[j] = claves[j-1];
        punteros[j+1] = punteros[j];
    }
    claves[i] = clave;
    punteros[i+1] = nuevo_hijo;
    p->set_num_claves(n+1);
    //si no está lleno
    if (p->get_num_claves() <= orden){
        return;
    }
    // si se llenó hay que hacer split
    int clave_promovida;
    NodoBPlusBase* nuevo_nodo;
    split_interno(p, clave_promovida, nuevo_nodo);
    //se sigue de forma recursiva hacia arriba
    insertar_en_padre(p, clave_promovida, nuevo_nodo);
}

ArbolBPlus::~ArbolBPlus(){}