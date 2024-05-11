#include <stdio.h>
#include <stdlib.h>
#include "Aux-Clases.cpp"
#include "Aux-Functions.cpp"
#include "Ciaccia-Patella.cpp"
#include <set>
#include <vector>
#include <algorithm>

using namespace std; 

int main(){
    Node nodo;
    Entry entrada1;
    Entry entrada2;
    Point punto1;
    Point punto2;
    Point punto3;
    Mtree arbol; 
    Conjunto_sample conjunto;
    set<Entry> a;
    set<Conjunto_sample> conjuntitos;

    punto1.x = 3;
    punto1.y = 8;
    punto2.x = 6;
    punto2.y = 4;
    punto3.x = 3;
    punto3.y = 4;

    vector<Point> v;
    v.push_back(punto1);
    v.push_back(punto2);
    v.push_back(punto3);
    
    printf("el tamaño del set antes de la eliminacion es %d\n",v.size());
    auto it = find(v.begin(), v.end(), punto1);
    v.erase(it);
    printf("el tamaño del set despues de la eliminacion es %d\n",v.size());
}
