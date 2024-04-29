#include <stdio.h>
#include <stdlib.h>

double dist(double p, double q){
    return abs(p-q)
}

void put(Node *n, double p, double cr, Node *a){
    Entry *place = *(n.List) + sizeof(Entry)*count;
    Entry e = {p,cr,a}
    *place = e;
}