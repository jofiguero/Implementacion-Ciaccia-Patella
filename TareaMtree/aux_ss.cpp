#include <iostream>
#include <stdio.h>
using namespace std;
#include <vector>
#include <tuple>
#include "aux_functions_cp.cpp"

Point closer(set<Point> samples, Point punto){
    double min_dif = DBL_MAX;
    Point mas_cercano;
    for(Point sample: samples){
        double dif = dist_eu(punto,sample);
        if (dif<min_dif){
            min_dif = dif;
            mas_cercano = sample;
        }
    }
    return mas_cercano;
}

Point meoide_set(set <Point> s){
    Point best = *s.begin();
    double min = DBL_MAX;
    set<Point>::iterator i;
    for (i = s.begin(); i!= s.end(); i++){
        double radio = 0;
        set<Point>::iterator j;
        for (j = s.begin(); j!= s.end(); j++){
            double dist = dist_eu(*i,*j);
            if(radio<dist && dist!= 0){
                radio = dist;
            }
        }
        if (radio<min){
            min = radio;
            best = *i;
        }
    }
    return best;
}

double radio_cobertor(set <Point> s){
    double min = DBL_MAX;
    set<Point>::iterator i;
    for (i = s.begin(); i!= s.end(); i++){
        double radio = 0;
        set<Point>::iterator j;
        for (j = s.begin(); j!= s.end(); j++){
            double dist = dist_eu(*i,*j);
            if(radio<dist && !(*i==*j)){
                radio = dist;
            }
        }
        if (radio<min){
            min = radio;
        }
    }
    return min;
}

double distancia_clusters(set<Point> n, set<Point> m){
    Point p = meoide_set(n);
    Point q = meoide_set(m);
    return dist_eu(p,q);
}

tuple< set<Point>, set<Point> > cluster_mas_cercanos(vector<set<Point>> clusters){
    set<Point> c1;
    set<Point> c2;
    double d_min = DBL_MAX;
    for (size_t i = 0; i < clusters.size(); i++) {
        for (size_t j = 0; j < clusters.size(); j++) {
            double dist = distancia_clusters(clusters[i],clusters[j]);
            if(dist<d_min && clusters[i].size() >= clusters[j].size() && i!=j){
                d_min = dist;
                c1 = clusters[i];
                c2 = clusters[j]; 
            }
        }
    }
    return make_tuple(c1,c2);
}

int same(set<Point> c1, set<Point> c2){
    if (c1.size() == c2.size()){
        set<Point>::iterator i;
        set<Point>::iterator j;
        i = c1.begin();
        j = c2.begin();
        for (int k = 0 ; k < c1.size(); k++){
            if (!(*i == *j)){
                return 0;
            }
            i++;
            j++;
        }
        return 1;
    }
    return 0;
}

int encontrar_cluster(vector<set<Point>> C, set<Point> cluster){
    for (size_t i = 0; i < C.size(); i++){
        if (same(C[i],cluster)){
            return i;
        }
    }
    return INT16_MAX;
}

// entrega el cluster más cercano al cluster pedido en un conjunto de clusters
set<Point> vecino_mas_cercano(vector<set<Point>> C, set<Point> cluster){
    double d_min = DBL_MAX;
    int pos;
    for (size_t i = 0; i < C.size(); i++){
        double dist = distancia_clusters(C[i],cluster);
        if (dist < d_min){
            d_min = dist;
            pos = i;
        }
    }
    return C[pos];
}