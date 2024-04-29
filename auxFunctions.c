#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.c"

double dist_entry(Entry n, Entry m){
    Point p = n.p;
    Point q = m.p;
    dif_x = p.x - q.x;
    dif_y = p.y - q.y;
    return sqrt(dif_x**2+dif**2);
}

double dist (Point p, Point q){
    dif_x = p.x - q.x;
    dif_y = p.y - q.y;

    return sqrt(dif_x**2+dif**2);
}

void put(Node *n, double p, double cr, Node *a){
    int place = n->count +1;
    n->list[place].p = p;
    n->list[place].cr = cr;
    n->list[place].a = a;
}