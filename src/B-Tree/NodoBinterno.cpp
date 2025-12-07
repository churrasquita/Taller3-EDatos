#include "NodoBInterno.h"

NodoBInterno::NodoBInterno(int orden):NodoBPlusBase(orden, false){
    punteros= new NodoBPlusBase*[orden + 1];
    for(int i=0; i<orden + 1; i++){
        punteros[i] = nullptr;
    }
}

NodoBInterno::~NodoBInterno() {
    delete[] punteros;
}

int NodoBInterno::buscar_siguiente(){
    return 0; // arreglar
}


