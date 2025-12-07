#include "NodoDirectorio.h"

NodoDirectorio::NodoDirectorio(int id):NodoGrafo(id) {}

bool NodoDirectorio::es_directorio() {
    return true;
}

int* NodoDirectorio::lista_hijos() {
    return nullptr;
}
NodoDirectorio::~NodoDirectorio() {}