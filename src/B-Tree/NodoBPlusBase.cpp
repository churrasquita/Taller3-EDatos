#include "NodoBPlusBase.h"

NodoBPlusBase::NodoBPlusBase(int orden, bool esHoja) {
    this->orden=orden;
    this->es_hoja=esHoja;
    this->claves=new int[orden]; 
}

NodoBPlusBase::~NodoBPlusBase() {
    delete[] claves;
}
