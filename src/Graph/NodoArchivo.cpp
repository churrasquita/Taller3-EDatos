#include "NodoArchivo.h"

NodoArchivo::NodoArchivo(int id, int tamaño, int tipo):NodoGrafo(id),tamaño(tamaño),tipo(tipo) {}

bool NodoArchivo::es_directorio() {
    return false;
}
NodoArchivo::~NodoArchivo() {}
