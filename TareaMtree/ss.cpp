#include <iostream>
#include <stdio.h>
using namespace std;
#include "cp.cpp"

int B = 4096 / sizeof(Entry);
int b = 0.5 * B;

double distancia_clusters_opt(Cluster_Puntos c1, Cluster_Puntos c2){
    return dist_eu(c1.m,c2.m);
}

int encontrar_cluster_opt(vector<Cluster_Puntos> C, Cluster_Puntos cluster){
    for (size_t i = 0; i < C.size(); i++){
        if (C[i]==cluster){
            return i;
        }
    }
    return INT16_MAX;
}

// entrega el cluster más cercano al cluster pedido en un conjunto de clusters
tuple<Cluster_Puntos, int> pos_vecino_mas_cercano_opt(vector<Cluster_Puntos> C, Cluster_Puntos cluster){
    double d_min = DBL_MAX;
    int pos;
    for (size_t i = 0; i < C.size(); i++){
        double dist = distancia_clusters_opt(C[i],cluster);
        if (dist < d_min){
            d_min = dist;
            pos = i;
        }
    }
    return make_tuple(C[pos],pos);
}

tuple< double, Cluster_Puntos, Cluster_Puntos > par_clusters_opt(Cluster_Puntos c, Point p, Point q){
    set<Point> c1;
    c1.insert(p);
    c.s.erase(p);
    set<Point> c2;
    c2.insert(q);
    c.s.erase(q);
    double cr;
    while (c.s.size()!=0){
        Point p1 = closer(c.s,p);
        c1.insert(p1);
        c.s.erase(p1);
        if (c.s.size()!=0){
            Point p2 = closer(c.s,q);
            c2.insert(p2);
            c.s.erase(p2)  ;
        }
    }
    int r1 = radio_cobertor(c1);
    int r2 = radio_cobertor(c2);
    cr = max(r1,r2);
    return make_tuple(cr,Cluster_Puntos(c1,r1),Cluster_Puntos(c2,r2));
}

tuple< Cluster_Puntos, Cluster_Puntos > min_max_split_opt(Cluster_Puntos c){
    Cluster_Puntos c1;
    Cluster_Puntos c2;
    double cr_min = DBL_MAX;
    set<Point>::iterator i;
    set<Point>::iterator j;
    for (i = c.s.begin(); i != c.s.end(); i++) {
        for (j = c.s.begin(); j != c.s.end(); j++) {
            if(!(*i==*j)){
                Cluster_Puntos cp1;
                Cluster_Puntos cp2;
                double cpr;
                tie(cpr,cp1,cp2) = par_clusters_opt(c,*i,*j);
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

vector<set<Point>> Cluster(set<Point> C_in){
    vector<Cluster_Puntos> C_out;
    vector<Cluster_Puntos> C;
    set<Point>::iterator itr;
    for (Point itr : C_in){
        Point *point = new Point();
        *point = itr;
        Cluster_Puntos *p = new Cluster_Puntos({*point});
        C.push_back(*p);
    }
    while (C.size()>1){
        Cluster_Puntos c1;
        Cluster_Puntos c2;
        tie(c1,c2) = par_mas_cercano(C);
        int size_union = c1.tamano + c2.tamano;
        if(size_union <= B){
            C.erase(C.begin()+ encontrar_cluster_opt(C,c1));
            C.erase(C.begin()+ encontrar_cluster_opt(C,c2));
            c1.fusionar(c2);
            C.push_back(c1);
        }
        else{
            C.erase(C.begin()+ encontrar_cluster_opt(C,c1));
            C_out.push_back(c1);
        }
    }
    Cluster_Puntos c = C[0];
    Cluster_Puntos cp;
    if (C_out.size()>0){
        int pos;
        tie(cp,pos) = pos_vecino_mas_cercano_opt(C_out, c);
        C_out.erase(C_out.begin()+ pos);
    }
    else{
        cp = {};
    }
    int size_union = c.tamano + cp.tamano;
    Cluster_Puntos c_cp;
    c.fusionar(cp);
    if (size_union > B){
        Cluster_Puntos c1;
        Cluster_Puntos c2;
        tie(c1,c2) = min_max_split_opt(c);
        C_out.push_back(c1);
        C_out.push_back(c2);
    }
    vector< set<Point>> C_out_v;
    for (size_t i = 0; i < C_out.size(); i++){
        C_out_v.push_back(C_out[i].s);
    }
    return C_out_v;
}


Entry OutputHoja(set<Point> C_in){
    set<Entry> C;
    Point *g = new Point();
    *g = meoide_set(C_in);
    double r = 0;
    set<Point>::iterator itr;
    for (itr = C_in.begin(); itr!= C_in.end(); itr++){
        Entry *entrada = new Entry(*itr);
        C.insert(*entrada);
        r = max(r,dist_eu(*g,*itr));
    }
    Node *nodo = new Node();
    nodo->entries = C;
    Mtree *a = new Mtree();
    a->root = nodo;
    return Entry(*g,r,a);
}

Entry OutputInterno(set<Entry> C_mra){
    set<Point> C_in;
    set<Entry>::iterator i;
    for (i = C_mra.begin(); i!= C_mra.end(); i++){
        C_in.insert(i->p);
    }
    Point *G = new Point();
    *G = meoide_set(C_in);
    double R = 0;
    set<Entry> C;
    set<Entry>::iterator j;
    for (j = C_mra.begin(); j!= C_mra.end(); j++){
        Entry e = *j;
        C.insert(e);
        R = max(R, dist_eu(*G,e.p) + e.cr);
    }
    Mtree *A = new Mtree();
    Node *nodo = new Node();
    nodo->entries = C;
    A->root = nodo;
    return Entry(*G,R,A);
}


Mtree AlgoritmoSS(set<Point> C_in){
    if (C_in.size() <= B){
        Entry *e = new Entry();
        *e = OutputHoja(C_in);
        return *e->a;
    }
    vector<set<Point>> C_out = Cluster(C_in);
    set<Entry> C;
    for (size_t i = 0; i < C_out.size(); i++){
        set<Point> points = C_out[i];
        set<Point>::iterator w;
        w = points.begin();
        Entry *e = new Entry();
        *e = OutputHoja(points);
        C.insert(*e);
    }
    while (C.size() > B){
        C_in = {};
        set<Entry>::iterator j;
        for (j = C.begin(); j!= C.end(); j++){
            C_in.insert(j->p);
        }
        C_out = Cluster(C_in);
        vector<set<Entry>> C_mra;
        C_mra = {};
        set<Entry> s;
        s = {};
        for (size_t k = 0; k < C_out.size(); k++){
            set<Point>::iterator c;
            for (c = C_out[k].begin(); c!= C_out[k].end(); c++){
                if(point_in_entries(*c,C)){
                    s.insert(*c);
                }
            }
        }
        C_mra.push_back(s);
        C = {};
        for (size_t m = 0; m < C_mra.size(); m++){
            Entry *e = new Entry();
            *e = OutputInterno(C_mra[m]);
            C.insert(*e);
        }
    }
    Entry e = OutputInterno(C);
    return *e.a;
}

