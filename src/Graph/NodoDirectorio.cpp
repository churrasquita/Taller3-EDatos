#include "NodoDirectorio.h"

NodoDirectorio::NodoDirectorio(int id):NodoGrafo(id) {
    lista = nullptr;
}

bool NodoDirectorio::es_directorio() {
    return true;
}

void NodoDirectorio::agregar_hijo(int id_hijo) {
    NodoHijo* nuevo = new NodoHijo;
    nuevo->id = id_hijo;
    nuevo->sig = nullptr;
    if(!lista) {
        lista = nuevo;
        return;
    }
    NodoHijo* aux = lista;
    while (aux->sig) aux = aux->sig;
    aux->sig = nuevo;
}

int* NodoDirectorio::lista_hijos() {
      // contar hijos
    int count = 0;
    NodoHijo* aux = lista;
    while (aux) {
        count++;
        aux = aux->sig;
    }

    if (count == 0) return nullptr;
    int* arr = new int[count + 1];

    aux = lista;
    int i = 0;
    while(aux) {
        arr[i++] = aux->id;
        aux = aux->sig;
    }
    arr[i] = -1; // termina
    return arr;
}



NodoDirectorio::~NodoDirectorio(){
    NodoHijo* aux = lista;
    while(aux){
        NodoHijo* tmp=aux;
        aux = aux->sig;
        delete tmp;
    }
}