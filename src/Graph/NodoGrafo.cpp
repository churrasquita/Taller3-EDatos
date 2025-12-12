#include "NodoGrafo.h"

NodoGrafo::NodoGrafo(int id){
    this->id = id;
    this->cabeza = nullptr;
}
bool NodoGrafo::es_directorio(){
    return false; 
}

int* NodoGrafo::lista_padres() {
    int count = 0; //contador de la cantidad de padres
    NodoPadre* temp = cabeza;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    // arreglo dinámico
    int* resultado = new int[count + 1];
    // volvemos a recorrer
    temp = cabeza;
    int i = 0;
    while(temp !=nullptr) {
        resultado[i++] =temp->id_padre;
        temp = temp->next;
    }
    resultado[i] = -1; // termina
    return resultado;
}


//método para agregar padres de forma dinámica
void NodoGrafo::agregar_padre(int id_padre) {
    NodoPadre* nuevo = new NodoPadre;
    nuevo->id_padre = id_padre;
    nuevo->next = cabeza;
    cabeza = nuevo;
}

NodoGrafo::~NodoGrafo(){
    NodoPadre* temp = cabeza;
    while (temp != nullptr) {
        NodoPadre* borrar = temp;
        temp = temp->next;
        delete borrar;
    }
}

