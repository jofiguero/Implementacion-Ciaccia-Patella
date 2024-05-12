#include <iostream>
#include <stdio.h>
using namespace std;
#include <vector>
#include<tuple>
#include <cmath>
#include <cfloat>
#include <cstdint>
#include "basic_blocks_ss.cpp"

double dist_eu(Point p, Point q){
    return sqrt(pow(p.x - q.x, 2)+pow(p.y - q.y, 2));
}

//retorna el punto del cluster que esté más cercano a un punto
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

//retorna el meoide de un vector de Points
// Point meoide_vec(vector<Point> cluster){
//     Point best;
//     double min = DBL_MAX;
//     for (size_t i = 0 ; i < cluster.size() ; i++){
//         double radio = 0;
//         for (size_t j = 0; j < cluster.size(); j++) {
//             double dist = dist_eu(cluster[i],cluster[j]);
//             if(radio<dist){
//                 radio = dist;
//             }
//         }
//         if (radio<min){
//             min = radio;
//             best = cluster[i];
//         }
//     }
//     return best;
// }

//retorna el meoide de un set de Points
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

//retorna la distancia entre 2 clusters(vector de Points)
// double distancia_clustersMALO(vector<Point> n, vector<Point> m){
//     Point p = meoide_vec(n);
//     Point q = meoide_vec(m);
//     return dist_eu(p,q);
// }

//retorna la distancia entre 2 clusters(vector de Points)
double distancia_clusters(set<Point> n, set<Point> m){
    Point p = meoide_set(n);
    Point q = meoide_set(m);
    return dist_eu(p,q);
}

//return el par de clusters(vector de Points) más cercanos de un vector de clusters
// tuple< vector<Point>, vector<Point> > cluster_mas_cercanosMALO(vector<vector<Point>> clusters){
//     vector<Point> c1;
//     vector<Point> c2;
//     double d_min = DBL_MAX;
//     for (size_t i = 0; i < clusters.size(); i++) {
//         for (size_t j = 0; j < clusters.size(); j++) {
//             double dist = distancia_clustersMALO(clusters[i],clusters[j]);
//             if(dist<d_min && clusters[i].size() >= clusters[j].size()){
//                 d_min = dist;
//                 c1 = clusters[i];
//                 c2 = clusters[j]; 
//             }
//         }
//     }
//     return make_tuple(c1,c2);
// }

//return el par de clusters(vector de Points) más cercanos de un vector de clusters
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

//el punto c está en las entradas de C
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

tuple< double, set<Point>, set<Point> > par_clusters(set<Point> c, Point p, Point q){
    set<Point> c1;
    c1.insert(p);
    c.erase(p);
    set<Point> c2;
    c2.insert(q);
    c.erase(q);
    double cr;
    while (c.size()!=0){
        Point p1 = closer(c,p);
        c1.insert(p1);
        c.erase(p1);
        if (c.size()!=0){
            Point p2 = closer(c,q);
            c2.insert(p2);
            c.erase(p2)  ;
        }
    }
    cr = max(radio_cobertor(c1),radio_cobertor(c2));
    return make_tuple(cr,c1,c2);
}

tuple< set<Point>, set<Point> > min_max_split(set<Point> c){
    set<Point> c1;
    set<Point> c2;
    double cr_min = DBL_MAX;
    set<Point>::iterator i;
    set<Point>::iterator j;
    for (i = c.begin(); i != c.end(); i++) {
        for (j = c.begin(); j != c.end(); j++) {
            if(!(*i==*j)){
                set<Point> cp1;
                set<Point> cp2;
                double cpr;
                tie(cpr,cp1,cp2) = par_clusters(c,*i,*j);
                if(cpr<cr_min){
                    cr_min = cpr;
                    c1 = cp1;
                    c2 = cp2;
                }
            }
            
        }
    }
    return make_tuple(c1,c2);
}












void saca(set<Point> c){
        c.erase(c.begin());
        set<Point>::iterator i;
        for (i = c.begin(); i != c.end(); i++){
            cout << i->x<<","<<i->y<< endl;
        }
    }

int main98(){
    set<Point> c;
    c.insert(Point(3,5));
    c.insert(Point(3,2));
    saca(c);
    set<Point>::iterator i;
    for (i = c.begin(); i != c.end(); i++){
        cout << i->x<<","<<i->y<< endl;
    }
    return 0;
}