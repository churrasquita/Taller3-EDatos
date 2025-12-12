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
    arbol->insertar_nodo_grafo(nuevo_id, nuevo);

    NodoDirectorio* pd = (NodoDirectorio*)padre;
    pd->agregar_hijo(nuevo_id);
    cout << "Node created successfully."<<endl;
}

void eliminar_archivo(int id_archivo, int id_directorio_padre) {
    int accesos = 0;
    NodoGrafo* archivo = arbol->buscar_nodo_grafo(id_archivo, accesos);
    if (!archivo) {
        cout << "File not found."<<endl;
        return;
    }

    if (archivo->es_directorio()) {
        cout << "The ID corresponds to a directory, not a file."<<endl;
        return;
    }

    NodoGrafo* padre = arbol->buscar_nodo_grafo(id_directorio_padre, accesos);
    if (!padre || !padre->es_directorio()) {
        cout <<"Parent directory not found."<<endl;
        return;
    }
    // eliminar id_archivo   
    NodoDirectorio* pd = (NodoDirectorio*)padre;
    int* hijos = pd->lista_hijos();
    if (hijos) {
        // reconstruir lista sin el archivo
        for (int i = 0; hijos[i] != -1; i++) {
            if (hijos[i] == id_archivo) {
                hijos[i] = -1;//eliminado
            }
        }
        // eliminar el arreglo
        delete[] hijos;
    }
    //eliminar referencia del padre
    int* padres = archivo->lista_padres();
    bool tiene_otros = false;
    for(int i = 0; padres[i] !=-1;i++) {
        if(padres[i] !=id_directorio_padre) {
            tiene_otros = true;
        }
    }
    delete[] padres;

    //borrar del B+
    if(!tiene_otros) {
        arbol->eliminar(id_archivo);
        cout << "File deleted completely.\n";
    } else {
        cout << "Parent reference removed.\n";
    }
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
    if (!hijos) {
        cout << "Directory is empty.\n";
        return;
    }
    cout << "Contents of directory " << id_directorio << ":\n";
    for (int i = 0; hijos[i] != -1; i++) {
        int hijo_id = hijos[i];
        int accesos2 = 0;
        NodoGrafo* hijo = arbol->buscar_nodo_grafo(hijo_id, accesos2);
        if (!hijo) continue;
        cout << "- ID: " << hijo_id;
        if (hijo->es_directorio())
            cout << "  (Directory)\n";
        else
            cout << "  (File)\n";
    }
    delete[] hijos;
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