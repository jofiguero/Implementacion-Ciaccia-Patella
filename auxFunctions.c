#include <stdio.h>
#include <stdlib.h>
#include "structures.c"

double dist_entry(Entry n, Entry m){
    double p = n.p;
    double q = m.p;
    return abs(p-q);
}

double dist (double p, double q){
    return abs(p-q);
}

void put(Node *n, double p, double cr, Node *a){
    int place = n->count +1;
    n->list[place].p = p;
    n->list[place].cr = cr;
    n->list[place].a = a;
}