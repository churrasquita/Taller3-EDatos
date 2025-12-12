#include "NodoBInterno.h"

NodoBInterno::NodoBInterno(int orden):NodoBPlusBase(orden, false){
    punteros = new NodoBPlusBase*[orden + 3];
    for(int i=0; i<orden+3; i++){
        punteros[i] = nullptr;
    }
}

NodoBPlusBase** NodoBInterno::get_punteros(){
    return punteros;
}

//método que dado una clave devuelve el id se baja por el árbol hasta encontrar el índice del puntero hijo
int NodoBInterno::buscar_siguiente(int clave){
    int* claves = get_claves();
    int n = get_num_claves();
    int i = 0;
    while(i <n&& clave >=claves[i]){
        i++;
    }
    return i;  // índice del puntero hijo
}

NodoBInterno::~NodoBInterno() {
    delete[] punteros;
}




