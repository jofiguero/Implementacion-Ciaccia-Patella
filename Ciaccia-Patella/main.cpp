#include <stdio.h>
#include <stdlib.h>
#include "Aux-Clases.cpp"
#include "Aux-Functions.cpp"
#include "Ciaccia-Patella.cpp"
#include <set>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>


using namespace std; 

vector<Point> generateRandomPoints(int numPoints) {
    vector<Point> points;

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 1.0);

    while (points.size() < numPoints) {
        Point p;
        p.x = dis(gen);
        p.y = dis(gen);
        points.push_back(p);
    }

    return points;
}



int main(){
    vector<Point> setp = generateRandomPoints(580); // Suponiendo que esta función genera 20 puntos aleatorios
    Mtree *m = CP(setp); // Construir el árbol a partir del conjunto de puntos generado

    ImprimeArbol2(*m);
    // Test: ver todas las entradas en el nodo raíz
    set<Entry>& entradas = m->root->entries;
    cout << "Size of entries in root node: " << entradas.size() << endl;


    // Imprimir las entradas en el nodo raíz
    printf("Llegue al final del programa!!\n");
    return 0;
  
}
