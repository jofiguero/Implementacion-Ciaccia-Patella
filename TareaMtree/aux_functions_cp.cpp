#ifndef AUX_CPP
#define AUX_CPP

#include <iostream>
#include <unordered_set>
#include <cstdlib>
#include <math.h>
#include <ctime>
#include <float.h>
#include <cmath>
#include <vector>
#include "aux_clases_cp.cpp"
using namespace std;

vector<Point> setAleatorio(vector<Point> conjunto, int k, int i) {
    vector<Point> muestra;
    srand(time(0) + i); // Modifica la semilla con un desplazamiento basado en i

    // Mientras el conjunto no esté vacío y la muestra no tenga el tamaño deseado
    while (!conjunto.empty() && muestra.size() < k) {
        // Selecciona un índice aleatorio dentro del rango del conjunto
        int index = rand() % conjunto.size();
        // Agrega el elemento seleccionado a la muestra
        muestra.push_back(conjunto[index]);
        // Elimina el elemento seleccionado del conjunto
        conjunto.erase(conjunto.begin() + index);
    }

    return muestra;
}

double dist (Point p, Point q){
    double dif_x = p.x - q.x;
    double dif_y = p.y - q.y;

    return sqrt(dif_x * dif_x + dif_y * dif_y);
}

Point closer(vector<Point> samples, Point punto){
    double min_dif = DBL_MAX;
    Point mas_cercano;
    for(Point sample: samples){
        double dif = dist(punto,sample);
        if (dif<min_dif){
            min_dif = dif;
            mas_cercano = sample;
        }
    }
    return mas_cercano;
}
int altura(Mtree *ptr_arbol) {
    // Si el nodo es NULL, el árbol tiene altura 0
    if (ptr_arbol == NULL) {
        return 0;
    }

    int alturaMaxima = 0;

    for (const Entry &entrada : ptr_arbol->root->entries) {
        int alturaSubarbol = altura(entrada.a);
        alturaMaxima = max(alturaMaxima, alturaSubarbol);
    }
    return alturaMaxima + 1;
};

int alturaMinima(vector<AS*> ASs) {
    int alturaMinima = numeric_limits<int>::max();
    for (AS* as : ASs) {
        int alturaArbol = altura(as->arbol);
        alturaMinima = min(alturaMinima, alturaArbol);
    }
    return alturaMinima;
};

/*Esta funcion recibe un punto y un set de entradas y tiene que devolver la distancia maxima que 
existe entre el punto y alguno de los puntos de las entradas*/
double crAux(Point padre,set<Entry> hijas){
    double distMax = 0;
    for(Entry hija: hijas){
        /*Se calcula la distancia entre el padre y la hija*/
        double distancia = dist(padre, hija.p);
        if(distancia>distMax){
            /*distMax se redefine como la distancia entre el padre y la hija*/
            distMax = distancia;
        }
    }
    return distMax;
}

/*Esta funcion recibe un puntero a un nodo, primero chequea que el nodo no sea una hoja, si lo es, 
retorna, si no, para cada entrada del nodo toma el punto y calcula la distancia maxima hacia algun 
punto perteneciente al nodo hijo, luego se llama recursivamente a sí misma en el hijo*/
void cr(Node *node){
    if(node == NULL ){
        return;
    }
    /*seleccionamos la lista de entradas del nodo*/
    set<Entry>& entradas = node->entries;

    /*seleccionamos la primera entrada*/
    Entry primeraEntrada = *(entradas.begin());
    if(primeraEntrada.a == NULL){
        return;
    }else{
        for(const Entry& entrada: entradas){
            Entry *ptr_no_constante = const_cast<Entry*>(&entrada);
            /*Seleccionamos el set de entradas del nodo hijo de la entrada*/
            set<Entry> entradas_hijas = entrada.a->root->entries ;
            /*Usamos una funcion auxiliar para calcular el cr de esta entrada*/
            double distancia_maxima = crAux(entrada.p, entradas_hijas);
            /*Le asignamos esta distancia a la entrada como cr*/
            ptr_no_constante->cr = distancia_maxima;
            /*Llamamos recursivamente la funcion en el nodo hijo de la entrada*/
            cr(ptr_no_constante->a->root);
        }
    }
}




/*Esta funcion recibe un puntero a un arbol, un punto que es el punto raiz de dicho arbol, un vector de AS y una altura h*/
void SubarbolesValidos(Mtree *ptr_arbol, Point sample, vector<AS*> *contenedor,vector<Point> *F,int h){
    if(ptr_arbol ==NULL || altura(ptr_arbol)<h){
        return;
    }else{
        if(altura(ptr_arbol)==h){
            /*Se crea un AS, se añade al vector de AS y retorno*/
            Mtree *newArbol = new Mtree(ptr_arbol->root);
            AS* newas = new AS(sample, newArbol);
            contenedor->push_back(newas);
            F->push_back(sample);
            return;
            
        }else{
            for(Entry entrada: ptr_arbol->root->entries){
                if(entrada.a != NULL){
                    /*llamamos la funcion sobre su hijo*/
                    SubarbolesValidos(entrada.a,entrada.p,contenedor,F,h);
                }
            }
            return;
        }
    }
    

    

}


int tieneHoja(Mtree arbol){
    int retorno = 0;
    for(Entry entrada: arbol.root->entries){
        if(entrada.a == NULL){
            retorno = 1;
        }
    }
    return retorno;
}
void unirArboles(Mtree *Tinf, Point sample, Mtree *Tsup){
    if(Tsup == NULL){
        return;
    }
    if(tieneHoja(*Tsup)){

        for(const Entry& entrada: Tsup->root->entries){
            if(entrada.a == NULL){
                if(entrada.p == sample){
                    Entry *ptr_no_constante = const_cast<Entry*>(&entrada);
                    ptr_no_constante->a = Tinf;
                    return;
                }
            }else{
                unirArboles(Tinf,sample,entrada.a);
            }
        }
        return;
    }else{
        for(const Entry& entrada: Tsup->root->entries){            
            if(entrada.a==NULL){
                return;
            }
            unirArboles(Tinf,sample,entrada.a);
        }
        return;
    }
}
/*
void unirArboles(Mtree *Tinf, Point sample, Mtree *Tsup) {
    Entry *puntero= buscarSample(*Tsup,sample);
    puntero->a = Tinf;
    return;
};
*/
bool comparePoints(const Point& p1, const Point& p2) {
    return (p1.x == p2.x && p1.y == p2.y);
}

void ImprimeArbol3(Mtree t1) {
    //Printear el segundo nivel
    printf("Primer nivel:\n");
    for(Entry entrada: t1.root->entries){
        printf("x = %f,y = %f,a = %p,cr = %f\n",entrada.p.x,entrada.p.y,entrada.a,entrada.cr);
    }
    printf("Segundo nivel:\n");
    for(Entry entrada: t1.root->entries){
        for(Entry entrada: (*entrada.a).root->entries){
            printf("x = %f,y = %f,a = %p,cr = %f\n",entrada.p.x,entrada.p.y,entrada.a,entrada.cr);
        }
        printf(";\n");

    }
    printf("Tercer nivel\n");
    //Printear el tercer nivel
    for(Entry entrada: t1.root->entries){
        for(Entry entrada: (*entrada.a).root->entries){
            if(entrada.a !=NULL){
                for(Entry entrada: (*entrada.a).root->entries ){
                    printf("x = %f,y = %f,a = %p,cr = %f\n",entrada.p.x,entrada.p.y,entrada.a,entrada.cr);
                }
                printf(";\n");
            }
        }
    }
    return;
}

void ImprimeArbol2(Mtree t1) {
    //Printear el segundo nivel
    printf("Primer nivel:\n");
    for(Entry entrada: t1.root->entries){
        printf("x = %f,y = %f,a = %p,cr = %f\n",entrada.p.x,entrada.p.y,entrada.a,entrada.cr);
    }
    printf("Segundo nivel:\n");
    if(!isLeaf(t1)){
        for(Entry entrada: t1.root->entries){
            if(entrada.a!=NULL){
                for(Entry entrada: (*entrada.a).root->entries){
                    printf("x = %f,y = %f,a = %p,cr = %f\n",entrada.p.x,entrada.p.y,entrada.a,entrada.cr);
                }
                printf(";\n");
            }
        }
    }

    return;
}
void ImprimeArbol1(Mtree t1) {
    //Printear el segundo nivel
    printf("Primer nivel:\n");
    for(Entry entrada: t1.root->entries){
        printf("x = %f,y = %f,a = %p,cr = %f\n",entrada.p.x,entrada.p.y,entrada.a,entrada.cr);
    }
    return;
}
#endif