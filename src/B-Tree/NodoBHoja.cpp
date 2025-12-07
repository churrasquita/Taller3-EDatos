#include "NodoBHoja.h"

NodoBHoja::NodoBHoja(int orden):NodoBPlusBase(orden, true)
{
    datos = new NodoGrafo*[orden];
    for(int i=0; i<orden;i++){
        datos[i]= nullptr;
    }
    siguienteHoja=nullptr;
}

NodoBHoja::~NodoBHoja() {
    delete[] datos;
}
