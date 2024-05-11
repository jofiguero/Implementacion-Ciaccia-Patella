#ifndef CLASES_CPP
#define CLASES_CPP

#include <stdlib.h>
#include <set>
#include <vector>
using namespace std; 

class Point{
    public:
    double x;
    double y;
};
inline bool operator<(const Point& p1, const Point& p2){
    if (p1.x != p2.x){
        return p1.x < p2.x;
    }
    else{
        return p1.y < p2.y;
    }
};
inline bool operator==(const Point& p1, const Point& p2)  {
    return p1.x == p2.x && p1.y == p2.y;
};
inline bool operator!=(const Point& p1, const Point& p2)  {
    return p1.x != p2.x || p1.y != p2.y;
};

class Entry{
    public:
    Point p;
    double cr;
    class Mtree *a;
};
inline bool operator<(const Entry& lhs, const Entry& rhs){
  return lhs.p < rhs.p;
};
inline bool operator==(const Entry& e1, const Entry& e2)  {
    return e1.p.x == e2.p.x && e1.p.y == e2.p.y && e1.cr == e2.cr && e1.a == e2.a;
};

class Node{
    public:
    set<Entry> entries;
};

class Mtree{
    public:
    Node *root;
    Mtree(Node *n): root(n) {}
};

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
    return as1.sample == as2.sample;
};

class Query{
    public:
    Point q;
    double r;

    Query (Point q, double r): q(q), r(r){}
 };

#endif