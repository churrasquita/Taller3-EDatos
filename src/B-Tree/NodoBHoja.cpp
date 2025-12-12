#include "NodoBHoja.h"

NodoBHoja::NodoBHoja(int orden):NodoBPlusBase(orden, true){
    this->datos = new NodoGrafo*[orden+2];
    for(int i = 0; i<orden+2;i++){
        datos[i] = nullptr;
    } 
    siguiente_hoja= nullptr;
}

NodoGrafo** NodoBHoja::get_datos(){return datos;}
NodoBHoja* NodoBHoja::get_siguiente(){return siguiente_hoja; }
void NodoBHoja::set_siguiente(NodoBHoja* siguiente){ siguiente_hoja = siguiente; }

void NodoBHoja::insertar_en_hoja(int clave, NodoGrafo* nodo){
    int n = get_num_claves();
    int i = n-1;
    // desplazar para insertar en orden creciente
    while(i >=0 &&get_claves()[i] >clave) {
        get_claves()[i+1] = get_claves()[i];
        datos[i+1] = datos[i];
        i--;
    }
    get_claves()[i+1] = clave;
    datos[i+1] = nodo;
    set_num_claves(n+1);
}

bool NodoBHoja::esta_llena(){
    //verifica que la hoja está llena, si es que el num de claves es mayor al orden
    return (get_num_claves() > get_orden());
}

NodoBHoja::~NodoBHoja() {
    delete[] datos;
}
