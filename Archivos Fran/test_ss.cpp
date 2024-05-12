#include <iostream>
#include <stdio.h>
#include <initializer_list>
#include <set>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <random>
#include "Ciaccia-Patella.cpp"
#include "busqueda.cpp"
using namespace std;


void testOutputHoja(set<Point> c1){
    Entry e = OutputHoja(c1);
    std::cout<< "La entrada tiene punto: ("<<e.p.x<<","<<e.p.y<<")"<<endl;
    std::cout<< "La entrada tiene cr: "<<e.cr<<endl;
    std::cout << "el nodo tiene "<< e.a->root->entries.size() <<" entradas"<< endl;
    set<Entry>::iterator h;
    for (h=e.a->root->entries.begin(); h!=e.a->root->entries.end();h++){
        std::cout<<endl;
        std::cout << "La entrada del nodo tiene punto: ("<<h->p.x<<","<<h->p.y<<")"<<endl;
        if(h->cr == NULL){
            std::cout << "La entrada del nodo tiene cr bien definido"<< endl;
        }
        else{
            std::cout << "La entrada del nodo tiene cr MAL definido"<< endl;
            break;
        }
        if(h->a == NULL){
            std::cout << "La entrada del nodo tiene a bien definido"<< endl;
        }
        else{
            std::cout << "La entrada del nodo tiene a MAL definido"<< endl;
            break;
        }
    }
    std::cout << endl;
}

set<Point> crea_puntos(int cantidad){
    set<Point> C;
    const long max_rand = 1000000L;
    double lower_bound = 0;
    double upper_bound = 1;
    uniform_real_distribution<double> unif(lower_bound,
                                           upper_bound);
    default_random_engine re;
    while(C.size()<cantidad){ 
    // Getting a random double value
        double variable = unif(re);
        C.insert(*new Point(variable,0));
    }
    return C;
}

void test_correctitud(int n){
    cout << "Comienza el test para 2^"<<n<<endl;
    set<Point> p = crea_puntos(pow(2,n));
    unsigned inicio, final;
    inicio = clock();
    Mtree m = AlgoritmoSS(p);
    final = clock();
    double tiempo = (double(final-inicio)/CLOCKS_PER_SEC);
    cout <<"    Un arbol con 2^"<<n<<"puntos tarda "<<tiempo<<" en crearse"<<endl;
    set<Point> encontrados;
    int accesos_nodo;
    Point pq = Point(0.3,0);
    tie(accesos_nodo, encontrados) = buscar(m,Query{pq,0.02});
    set<Point> control;
    set<Point>::iterator h;
    for (h = p.begin(); h != p.end(); h++){
        if (dist_eu(pq,*h)<=0.02){
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
    set<Point> puntos = crea_puntos(pow(2,n));
    unsigned inicio, final;
    inicio = clock();
    Mtree tree = AlgoritmoSS(puntos);
    final = clock();
    double tiempo = (double(final-inicio)/CLOCKS_PER_SEC);
    cout <<"    Un arbol con 2^"<<n<<"puntos tarda "<<tiempo<<" en crearse"<<endl;
    test_100_busquedas(tree);
    cout << "Finaliza el test para 2^"<<n<<endl;
}

int main6(){
    set<Point> p = crea_puntos(300);
    Mtree m = AlgoritmoSS(p);
    set<Entry>::iterator h;
    std::cout << "primer nodo:"<<endl;
    set<Entry> e = m.root->entries;
    for (h = e.begin(); h != e.end(); h++){
        std::cout<< "("<<h->p.x<<","<<h->p.y<<") ";  
    }
    std::cout << "segundo nodo:"<<endl;
    set<Entry> g = m.root->entries.begin()->a->root->entries;
    for (h = g.begin(); h != g.end(); h++){
        std::cout<< "("<<h->p.x<<","<<h->p.y<<") ";  
    }
    return 0;
}
int mainfalso(){
    for (int i = 10; i<=25; i++){
        test_arbol(i);
    }
    return 0;
}
int main(){
    test_arbol(8);
    //test_correctitud(8);
    //test_correctitud(9);
    return 0;
}