
#include <iostream>
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "aux_functions_cp.cpp"
#include "cp.cpp"


using namespace std;

class Cluster_Puntos{
    public:
    set<Point> s;
    Point m; // meoide de s
    int tamano;

    Cluster_Puntos (set<Point> s): s(s), m(meoide_set(s)), tamano(s.size()){}
    Cluster_Puntos (set<Point> s, int t): s(s), m(meoide_set(s)), tamano(t){}
    Cluster_Puntos(){}

    void fusionar(Cluster_Puntos ns){
        tamano += ns.tamano;
        s.insert(ns.s.begin(),ns.s.end());
        m = meoide_set(s);
    }
};

inline bool operator<(const Cluster_Puntos& lhs, const Cluster_Puntos& rhs){
    return lhs.m < rhs.m; 
}
inline bool operator==(const Cluster_Puntos& c1, const Cluster_Puntos& c2){
    return c1.m == c2.m;
}

#include <vector>
using namespace std;

void swap(vector<Cluster_Puntos> &v, int x, int y) {
    Cluster_Puntos temp = v[x];
    v[x] = v[y];
    v[y] = temp;
}

void quicksortx(vector<Cluster_Puntos> &vec, int L, int R) {
    int i, j, mid;
    double piv;
    i = L;
    j = R;
    mid = L + (R - L) / 2;
    piv = vec[mid].m.x;
    while (i<R || j>L) {
        while (vec[i].m.x < piv)
            i++;
        while (vec[j].m.x > piv)
            j--;

        if (i <= j) {
            swap(vec, i, j);
            i++;
            j--;
        }
        else {
            if (i < R)
                quicksortx(vec, i, R);
            if (j > L)
                quicksortx(vec, L, j);
            return;
        }
    }
}

void quicksorty(vector<Cluster_Puntos> &vec, int L, int R) {
    int i, j, mid;
    double piv;
    i = L;
    j = R;
    mid = L + (R - L) / 2;
    piv = vec[mid].m.y;

    while (i<R || j>L) {
        while (vec[i].m.y < piv)
            i++;
        while (vec[j].m.y > piv)
            j--;

        if (i <= j) {
            swap(vec, i, j);
            i++;
            j--;
        }
        else {
            if (i < R)
                quicksorty(vec, i, R);
            if (j > L)
                quicksorty(vec, L, j);
            return;
        }
    }
}

tuple<Cluster_Puntos,Cluster_Puntos,double> bruteForce(vector<Cluster_Puntos> P, int n){
    Cluster_Puntos c1;
    Cluster_Puntos c2;
    double min = DBL_MAX;

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            double d = dist_eu(P[i].m, P[j].m);
            if ( d < min && d != 0){
                min = d;
                c1 = P[i];
                c2 = P[j];
            }
        }
    }
    return make_tuple(c1,c2,min);
}

tuple<Cluster_Puntos, Cluster_Puntos, double> stripClosest(vector<Cluster_Puntos> strip, int size, double d, Cluster_Puntos ca, Cluster_Puntos cb){

    double min = d;
    Cluster_Puntos c1=ca;
    Cluster_Puntos c2=cb;

    for (int i = 0; i < size; ++i){
       for (int j = i+1; j < size && (strip[j].m.y - strip[i].m.y) < min; ++j){
            double dist = dist_eu(strip[i].m,strip[j].m);
            if (dist < min && dist != 0){
                min = dist;
                c1=strip[i];
                c2=strip[j];
            }
        } 
    }

    return make_tuple(c1,c2,min);
}
 
tuple<Cluster_Puntos, Cluster_Puntos, double>closestUtil(vector<Cluster_Puntos> Px, vector<Cluster_Puntos> Py, int n){

    if (n <= 3){
        return bruteForce(Px, n);
    }
 
    int mid = n/2;

    Cluster_Puntos midPoint = Px[mid];
 
    vector<Cluster_Puntos> Pyl;
    vector<Cluster_Puntos> Pyr;

    int li = 0, ri = 0;
    for (int i = 0; i < n; i++){
        if ((Py[i].m.x < midPoint.m.x || (Py[i].m.x == midPoint.m.x && Py[i].m.y < midPoint.m.y)) && li<mid){
            Pyl.push_back(Py[i]);
            li++;
        }
        else{
            Pyr.push_back(Py[i]);
            ri++;
        }
    }

    vector<Cluster_Puntos> P_l;
    for(int a = 0; a<mid; a++){
        P_l.push_back(Px[a]);
    }
    Cluster_Puntos c1l;
    Cluster_Puntos c2l;
    double dl;
    tie(c1l,c2l,dl) = closestUtil(P_l, Pyl, P_l.size());
    vector<Cluster_Puntos> P_r;
    for(int z = mid; z<n; z++){
        P_r.push_back(Px[z]);
    }
    Cluster_Puntos c1r;
    Cluster_Puntos c2r;
    double dr;
    tie(c1r,c2r,dr)= closestUtil(P_r, Pyr, P_r.size());
 
    Cluster_Puntos c1m;
    Cluster_Puntos c2m;
    double d = min(dl, dr);
    if(dl<dr){
        c1m=c1l;
        c2m=c2l;
    }
    else{
        c1m=c1r;
        c2m=c2r;
    }
    vector<Cluster_Puntos> strip;
    int j=0;
    for (int w = 0; w < n; w++){
       if (abs(Py[w].m.x - midPoint.m.x) < d){
            strip.push_back(Py[w]);
            j++;
        } 
    }
    return stripClosest(strip, j, d,c1m,c2m);
}

tuple<Cluster_Puntos,Cluster_Puntos> par_mas_cercano(vector<Cluster_Puntos> P){
    vector<Cluster_Puntos> Px;

    vector<Cluster_Puntos> Py;

    int n = P.size();

    for (size_t i = 0; i < n; i++){
        Px.push_back(P[i]);
        Py.push_back(P[i]);
    }
    quicksortx(Px, 0, n-1);
    quicksorty(Py, 0, n-1);

    Cluster_Puntos c1;
    Cluster_Puntos c2;
    double d;
    tie(c1,c2,d) = closestUtil(Px, Py, n);

    return make_tuple(c1,c2);
}