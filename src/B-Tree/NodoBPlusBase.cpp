#include "NodoBPlusBase.h"

NodoBPlusBase::NodoBPlusBase(int orden, bool esHoja) {
    this->orden=orden;
    this->es_hoja=esHoja;
    this->claves=new int[orden+2]; // no es [orden] ya que se reserva espacio por los splits
    this->num_claves =0; 
}
int* NodoBPlusBase::get_claves() {return claves;}
int NodoBPlusBase::get_orden() {return orden;}
bool NodoBPlusBase::es_Hoja() {return es_hoja;}
int NodoBPlusBase::get_num_claves() {return num_claves;}
void NodoBPlusBase::set_num_claves(int cant_claves) {num_claves = cant_claves;}
    
NodoBPlusBase::~NodoBPlusBase() {
    delete[] claves;
}
