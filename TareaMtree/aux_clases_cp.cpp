#ifndef CLASES_CPP
#define CLASES_CPP

#include <stdlib.h>
#include <set>
#include <vector>
using namespace std; 
#include "aux_fun.cpp"

class Conjunto_sample{
    public:
    Point sample;
    vector<Point> conjunto;
    Conjunto_sample(Point s) : sample(s) {}
    void agregarPunto(Point nuevoPunto) {
        conjunto.push_back(nuevoPunto);
    }
} ;
inline bool operator<(const Conjunto_sample& c1, const Conjunto_sample& c2){
  return c1.sample < c2.sample;
};
inline bool operator>(const Conjunto_sample& c1, const Conjunto_sample& c2){
  return c1.sample > c2.sample;
};
inline bool operator==(const Conjunto_sample& c1, const Conjunto_sample& c2){
  return c1.sample == c2.sample;
};
inline bool operator!=(const Conjunto_sample& c1, const Conjunto_sample& c2){
  return c1.sample != c2.sample;
};

class AS{
    public:
    Point sample;
    Mtree *arbol;

    AS(Point s, Mtree *a) : sample(s), arbol(a) {}
};
inline bool operator<(const AS& as1, const AS& as2){
  return as1.sample < as2.sample;
};
inline bool operator==(const AS& as1, const AS& as2)  {
    return as1.sample == as2.sample && as1.arbol == as2.arbol;
};

#endif