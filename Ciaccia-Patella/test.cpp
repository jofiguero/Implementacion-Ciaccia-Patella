#include <stdio.h>
#include <stdlib.h>
#include "Aux-Clases.cpp"
#include "Aux-Functions.cpp"
#include "Ciaccia-Patella.cpp"
#include "busqueda.cpp"
#include <set>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>

using namespace std; 
vector<Point> crea_puntos(int cantidad){
    vector<Point> C;
    const long max_rand = 1000000L;
    double lower_bound = 0;
    double upper_bound = 1;
    uniform_real_distribution<double> unif(lower_bound,
                                           upper_bound);
    default_random_engine re;
    while(C.size()<cantidad){ 
    // Getting a random double value
        double variable = unif(re);
        C.push_back(*new Point(variable,0));
    }
    return C;
}
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
void test_correctitud(int n){
    cout << "Comienza el test para 2^"<<n<<endl;
    vector<Point> p = generateRandomPoints(pow(2,n));
    unsigned inicio, final;
    inicio = clock();
    Mtree *ptr_m = CP(p);
    Mtree m = *ptr_m;
    final = clock();
    double tiempo = (double(final-inicio)/CLOCKS_PER_SEC);
    cout <<"    Un arbol con 2^"<<n<<"puntos tarda "<<tiempo<<" en crearse"<<endl;
    set<Point> encontrados;
    int accesos_nodo;
    Point pq = Point(0.3,0);
    tie(accesos_nodo, encontrados) = buscar(m,Query{pq,0.02});
    set<Point> control;
    set<Point>::iterator h;
    for (Point punto: p){
        if (dist(pq,punto)<=0.02){
          control.insert(*h);
        }
    }
    cout << "  Accesos a nodo por la busqueda: "<< accesos_nodo<< endl;;
    if(control == encontrados){
        cout << "Paso el test para 2^"<<n<<endl;
    }
    else{
        cout << "Fallo el test para 2^"<<n<<endl;
    }
}
tuple<int , double> test_busqueda(Mtree tree, Point p){
    int accesos_nodo;
    set<Point> encontrados;
    unsigned inicio, final;
    inicio = clock();
    tie(accesos_nodo, encontrados) = buscar(tree, Query{p,0.02});
    final = clock();
    double tiempo = (double(final-inicio)/CLOCKS_PER_SEC);
    return make_tuple(accesos_nodo, tiempo);
}
double media(set<double> s){
    double total = 0;
    for(double n : s){
        total+=n;
    }
    return total/s.size();
}

double desviacion(set<double> s){
    double prom = media(s);
    double numerador = 0;
    for(double n : s){
        numerador += pow(abs(n - prom),2);
    }
    return sqrt(numerador/s.size());
}

void test_100_busquedas(Mtree tree){

    const long max_rand = 1000000L;
    double lower_bound = 0;
    double upper_bound = 1;
    uniform_real_distribution<double> unif(lower_bound,upper_bound);
    default_random_engine re;

    set<double> accesos;
    set<double> tiempos;

    for(int i=1; i<=100; i++){
       double variable = unif(re);
       Point p = Point(variable, 0);
       int funciona, a;
       double t;
       tie(a,t) = test_busqueda(tree, p);
       accesos.insert(a);
       tiempos.insert(t);
    }
    double desviacion_accesos = desviacion(accesos);
    double media_accesos = media(accesos);
    double desviacion_tiempo = desviacion(tiempos);
    double media_tiempo = media(tiempos);
    cout<<"    Los accesos tienen una desviacion estandar de : "<< desviacion_accesos<< endl;
    cout<<"    Los accesos tienen una media de : "<< media_accesos<< endl;
    cout<<"    Los tiempos tienen una desviacion estandar de : "<< desviacion_tiempo<< endl;
    cout<<"    Los tiempos tienen una media de : "<< media_tiempo<< endl;
}
void test_arbol(int n){
    cout << "Comienza el test para 2^"<<n<<endl;
    vector<Point> puntos = generateRandomPoints(pow(2,n));
    unsigned inicio, final;
    inicio = clock();
    Mtree *tree = CP(puntos);
    final = clock();
    double tiempo = (double(final-inicio)/CLOCKS_PER_SEC);
    cout <<"    Un arbol con 2^"<<n<<"puntos tarda "<<tiempo<<" en crearse"<<endl;
    test_100_busquedas(*tree);
    cout << "Finaliza el test para 2^"<<n<<endl;
}
int mainfalso(){
    test_arbol(16);
    return 0;
}
int main(){
    for (int i = 10; i<=25; i++){
        test_arbol(i);
    }
    return 0;
}

