#include "NodoGrafo.h"
#include "ArbolBPlus.h"
#include "NodoDirectorio.h"
#include "NodoArchivo.h"
#include <iostream>
using namespace std;
ArbolBPlus* arbol = new ArbolBPlus(4); 


void buscar_nodo(int clave){
    int accesos = 0; 
    NodoGrafo* nodo = arbol->buscar_nodo_grafo(clave, accesos);
    if(nodo){
        cout<<"- Node ID: "<<clave<<endl;
        cout<<"- Access B+: "<<accesos<<endl;
        if(nodo->es_directorio()) {
            cout<<"- Type: Directory"<<endl;
        } else {
            cout<<"- Type: Archive"<<endl;
        }
    } else {
        cout<<"Node NOT found"<<endl;
        cout<< "- Access B+: " << accesos << endl;
    }
}

void crear_nodo(int id_padre) {
    // ver si existe el padre
    int accesos = 0; 
    NodoGrafo* padre = arbol->buscar_nodo_grafo(id_padre, accesos);
    if (!padre) {
        cout<<"The parent directory doesn't exist." <<endl;
        return;
    }
    if (!padre->es_directorio()) {
        cout << "The ID doesn't correspond to a directory."<<endl;
        return;
    }
    // nuevo nodo
    cout << "- New ID: ";
    int nuevo_id;cin>>nuevo_id;
    cout << "- The new node is directory? (1:yes/0:no): ";
    int es_directorio;cin >> es_directorio;

    NodoGrafo* nuevo;
    if(es_directorio == 1) {
        nuevo = new NodoDirectorio(nuevo_id); //corresponde a un nodo directorio
    }else{
        cout<<"- File Size: "; 
        int tam;cin >>tam;
        cout << "- File type (0: Image; 1: Document; 2: Executable; 3: Video; 4: Compressed): ";
        int t; cin>>t;
        nuevo = new NodoArchivo(nuevo_id,tam,t); // es un nodo archivo
    }

    // ahora que ya sabemos el tipo de archivo, lo insertamos
    arbol->insertar_nodo_grafo(nuevo_id, nuevo);

    // agregar hijo en el directorio padre
    NodoDirectorio* dir = (NodoDirectorio*) padre; 
    int* hijos = dir->lista_hijos();
    for(int i = 0; i<20; i++) {
        if (hijos[i] == -1) { // primera casilla libre
            hijos[i] =nuevo_id;
            break;
        }
    }
    // agregar padre al nuevo nodo
    int* padres = nuevo->lista_padres();
    for(int i = 0; i <20; i++) {
        if(padres[i] ==-1) {
            padres[i] = id_padre;
            break;
        }
    }
    cout << "Node created successfully."<<endl;
}

void eliminar_archivo(int id_archivo, int id_directorio_padre) {
    int accesos = 0;
    NodoGrafo* archivo = arbol->buscar_nodo_grafo(id_archivo,accesos);
    NodoGrafo* padre = arbol->buscar_nodo_grafo(id_directorio_padre,accesos);
    if (!archivo || !archivo->es_directorio()) {
        cout << "The archive doesn't exist/isn't directory."<<endl;
        return;
    }
    if (!padre ||!padre->es_directorio()) {
        cout<<"The father doesn't exist/isn't directory."<<endl;
        return;
    }
    // se sigue sólo si es que el padre es directorio
    NodoDirectorio* dir = (NodoDirectorio*) padre; 
    //eliminar desde los hijos 
    int* hijos = dir->lista_hijos();
    for (int i = 0; i < 20; i++) {
        if (hijos[i] == id_archivo) {
            hijos[i] = -1;
            break;
        }
    }
    //eliminar archivos
    int* padres = archivo->lista_padres();
    for(int i = 0; i <20;i++) {
        if (padres[i] == id_directorio_padre) {
            padres[i] = -1;
            break;
        }
    }
    bool tiene_padre = false;
    for(int i = 0; i <20;i++) {
        if (padres[i] !=-1) {
            tiene_padre = true;
            break;
        }
    }
    if (!tiene_padre) {
        cout << "The file has no more parents"<<endl;
        arbol->eliminar(id_archivo); 
    }
    cout << "The file has been deleted succesfully."<<endl;
}

//método que busca en el directorio del árbol
void listar_contenido(int id_directorio) {
    int accesos = 0;
    NodoGrafo* dir = arbol->buscar_nodo_grafo(id_directorio, accesos);
    if (!dir ||!dir->es_directorio()) {
        cout << "The node doesn't exist/isn't directory."<<endl;
        return;
    }
    NodoDirectorio* dir2 = (NodoDirectorio*) dir; 
    int* hijos = dir2->lista_hijos();
    cout << "Directory contents (" << id_directorio << "):"<<endl;

    for(int i = 0; i <20; i++) {
        if (hijos[i] != -1) {
            int accesos2 = 0;
            NodoGrafo* hijo = arbol->buscar_nodo_grafo(hijos[i], accesos2);
            if(!hijo) continue;
            cout <<"- ID: "<< hijos[i];
            if(hijo->es_directorio()) {
                cout << " - Directory";
            } else{
                cout <<"  - Archive";
            }
            cout <<endl;
        }
    }
    cout << endl;
}

string* obtener_rutas_completas(int id_archivo){
    return nullptr;
}
int calcular_espacio_ocupado(int id_directorio){
    return 0; 
}

int main(){
    cout<<"Welcome!!"<<endl;
    cout<<"Let's try the file system"<<endl;
    string op = " "; 

    while(op!="8"){
        cout<<endl; 
        cout<<"---- MENU ----"<<endl;
        cout<<"1) Insert graph node "<<endl;
        cout<<"2) Search graph node"<<endl;
        cout<<"3) Create node"<<endl;
        cout<<"4) Delete file"<<endl;
        cout<<"5) List content"<<endl;
        cout<<"6) Obtain complete routes"<<endl;
        cout<<"7) Calculate occupied space"<<endl;
        cout<<"8) Exit"<<endl;
        cout<<">> ";
        cin>>op; 

        if(op == "1"){
            int clave;
            cout<<"- Node ID: ";
            cin>>clave;
            NodoGrafo* nodo_grafo = new NodoGrafo(clave); 
            arbol->insertar_nodo_grafo(clave, nodo_grafo);
        }
        else if(op=="2"){  
            cout<<"- Node ID: ";
            int clave; cin>>clave;
            buscar_nodo(clave);
        }
        else if(op=="3"){
            cout<<"- Parent Node ID: ";
            int id_padre;cin>>id_padre;
            crear_nodo(id_padre);
        }
        else if(op == "4"){
            int id_archivo, id_directorio_padre;
            cout<<"- File ID: ";
            cin>>id_archivo;
            cout<<"- Parent directory ID: ";
            cin>>id_directorio_padre;
            eliminar_archivo(id_archivo,id_directorio_padre);
        }
        else if(op == "5"){
            cout<<"- Directory ID: ";
            int id_directorio;cin>>id_directorio;
            listar_contenido(id_directorio);
        }
        else if(op == "6"){
            cout<<"- File ID: ";
            int id_archivo;cin>>id_archivo;
            obtener_rutas_completas(id_archivo);
        }
        else if(op == "7"){
            cout<<"- Directory ID";
            int id_directorio;cin>>id_directorio;
            calcular_espacio_ocupado(id_directorio);
        }
        else if(op == "8"){
            cout<<"See u later!"<<endl;
        }else{
            cout<<"Invalid option, pls try again :("<<endl;
            cout<<endl; 
        }
    }
 
    return 0;
}