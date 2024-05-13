#include <iostream>
#include <stdio.h>
using namespace std;
#include "clases.cpp"


int point_in_entries(Point p, set<Entry> E){
    set<Entry>::iterator itr;
    for (itr = E.begin(); itr!= E.end(); itr++){
        if (itr->p == p){
            return 1;
        }
    }
    return 0;
}

int isLeaf(Mtree tree){
    if(tree.root->entries.begin()->a == NULL){
        return 1;
    }
    return 0;
}

double dist_eu(Point p, Point q){
    return sqrt(pow(p.x - q.x, 2)+pow(p.y - q.y, 2));
}

