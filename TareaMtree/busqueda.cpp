#include <iostream>
#include <stdio.h>
using namespace std;
#include "aux_fun.cpp"
#include <tuple>


tuple < int , set <Point> >buscar(Mtree tree, Query Q){
    int n = 1;
    set <Point> s;
    if (isLeaf(tree)){
        set<Entry>::iterator itr;
        for (itr = tree.root->entries.begin(); itr!= tree.root->entries.end(); itr++) {
            if (dist_eu(itr->p, Q.q) <= Q.r){
                s.insert(itr->p);
            }
        }
    }
    else {
        set<Entry>::iterator itr2;
        for (itr2 = tree.root->entries.begin(); itr2!= tree.root->entries.end(); itr2++) {
            if (dist_eu(itr2->p, Q.q) <= itr2->cr + Q.r){
                set <Point> s2;
                int n2;
                tie(n2, s2) = buscar(*itr2->a, Q);
                s.insert(s2.begin(), s2.end());
                n += n2;
            }
        }
    }
    return make_tuple(n,s);
}