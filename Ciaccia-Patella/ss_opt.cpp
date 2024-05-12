#include <iostream>
#include <stdio.h>
using namespace std;
#include "ulrimo_intento.cpp"

int B = 4096 / sizeof(Entry);
int b = 0.5 * B;

// class Cluster_Puntos{
//     public:
//     set<Point> s;
//     Point m; // meoide de s
//     int tamano;

//     Cluster_Puntos (set<Point> s): s(s), m(meoide_set(s)), tamano(s.size()){}
//     Cluster_Puntos (set<Point> s, int t): s(s), m(meoide_set(s)), tamano(t){}
//     Cluster_Puntos(){}

//     void insertar(Cluster_Puntos ns){
//         s.insert(ns.s.begin(),ns.s.end());
//         m = meoide_set(s);
//         tamano += ns.tamano;
//     }
// };

// inline bool operator<(const Cluster_Puntos& lhs, const Cluster_Puntos& rhs){
//     return lhs.m < rhs.m; 
// }
// inline bool operator==(const Cluster_Puntos& c1, const Cluster_Puntos& c2){
//     if (c1.tamano != c2.tamano){
//         return 0;
//     }
//     if (!(c1.m == c2.m)){
//         return 0;
//     }
//     return c1.m == c2.m;
// }

double distancia_clusters_opt(Cluster_Puntos c1, Cluster_Puntos c2){
    return dist_eu(c1.m,c2.m);
}

tuple< Cluster_Puntos, Cluster_Puntos > cluster_mas_cercanos_opt(vector<Cluster_Puntos> clusters){
    Cluster_Puntos c1;
    Cluster_Puntos c2;
    double d_min = DBL_MAX;
    for (size_t i = 0; i < clusters.size(); i++) {
        for (size_t j = 0; j < clusters.size(); j++) {
            if(clusters[i].tamano >= clusters[j].tamano && i!=j){
                double dist = distancia_clusters_opt(clusters[i],clusters[j]);
                if(dist<d_min){
                    d_min = dist;
                    c1 = clusters[i];
                    c2 = clusters[j]; 
                }
            }
            
        }
    }
    return make_tuple(c1,c2);
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

// tuple< Cluster_Puntos, Cluster_Puntos > cluster_mas_cercanos_rayo(vector<Cluster_Puntos> clusters){
//     cout << "se tienen para elegir una cantidad de clusters "<<clusters.size()<<endl;
//     Cluster_Puntos c1;
//     Cluster_Puntos c2;
//     double d_min = closest(clusters);
//     //cout<<"los clusters mas cercanos estan a distancia "<<d_min<<endl;
//     for (size_t i = 0; i < clusters.size(); i++) {
//         //cout<<"probando el "<<i+1<<" elemento de C"<<endl;
//         for (size_t j = i + 1 ; j < clusters.size(); j++) {
//             double dif = dist_eu(clusters[i].m, clusters[j].m);
//             if(dif==0){
//                 cout<<"la distancia encontrada es "<<dif<< " con los clusters "<< i<< " y "<< j<<endl;
//             }
//             if(dif == d_min){
//             //cout<<"probando el "<<i+1<<" con el "<<j+1<<" elemento de C"<<endl;    
//                 if(clusters[i].tamano > clusters[j].tamano){
//                     c1 = clusters[i];
//                     c2 = clusters[j];
//                 }
//                 else{
//                     c1 = clusters[j];
//                     c2 = clusters[i];
//                 }
//                 return make_tuple(c1,c2);
//                 cout << "Los clusters mas cercanos dentro de clusters_rayo tienen tamanos "<<c1.s.size()<<" y "<<c2.s.size()<< endl;
//             }
//         }
//     }
//     cout << "Los clusters mas cercanos dentro de clusters_rayo al terminar el for "<<c1.s.size()<<" y "<<c2.s.size()<< endl;
//     return make_tuple(c1,c2);
// }

// tuple< Cluster_Puntos, Cluster_Puntos > cluster_mas_cercanos_rayo_2(vector<Cluster_Puntos> clusters){
//     Cluster_Puntos c1;
//     Cluster_Puntos c2;
//     double d_min = closest(clusters);
//     for (size_t i = 0; i < clusters.size(); i++) {
//         for (size_t j = i ; j < clusters.size(); j++) {
//             double d = distancia_clusters_opt(clusters[i],clusters[j]);
//             if(d == d_min){
//             //cout<<"probando el "<<i+1<<" con el "<<j+1<<" elemento de C"<<endl;    
//                 if(clusters[i].tamano >= clusters[j].tamano){
//                     c1 = clusters[i];
//                     c2 = clusters[j];
//                 }
//                 else{
//                     c1 = clusters[j];
//                     c2 = clusters[i];
//                 }
//                 return make_tuple(c1,c2);
//             }
//         }
//     }
//     return make_tuple(c1,c2);
// }

// tuple< Cluster_Puntos, Cluster_Puntos > cluster_mas_cercanos_rayo_3(vector<Cluster_Puntos> clusters){
//     Cluster_Puntos c1;
//     Cluster_Puntos c2;
//     tie(c1,c2) = closest_3(clusters);
//     return make_tuple(c1,c2);
// }

//BUENA
vector<set<Point>> Cluster2(set<Point> C_in){
    vector<Cluster_Puntos> C_out;
    vector<Cluster_Puntos> C;
    set<Point>::iterator itr;
    for (Point itr : C_in){
        Point *point = new Point();
        *point = itr;
        Cluster_Puntos *p = new Cluster_Puntos({*point});
        C.push_back(*p);
    }
    //cout << "cluster comienza con un vector de sigletons de tamano:"<<C.size()<<endl;
    while (C.size()>1){
        Cluster_Puntos c1;
        Cluster_Puntos c2;
        tie(c1,c2) = closest(C);
        //cout << "pasa el closest"<<endl;
        //cout << "Los clusters mas cercanos tienen tamanos "<<c1.s.size()<<" y "<<c2.s.size()<< endl;
        int size_union = c1.tamano + c2.tamano;
        if(size_union <= B){
            //cout << "fusiono clusters de tamano "<<c1.s.size()<<" y "<<c2.s.size()<<endl;
            C.erase(C.begin()+ encontrar_cluster_opt(C,c1));
            C.erase(C.begin()+ encontrar_cluster_opt(C,c2));
            //cout<<"cambiamos "<< c1.m.x<<" , " <<c1.m.y<< " por ";
            c1.fusionar(c2);
            //cout << c1.m.x<<" , " <<c1.m.y<<endl;
            C.push_back(c1);
            //cout << "Agrego a C un cluster de tamano: "<<c1.s.size()<<endl;
            //cout << "Ahora C tiene una cantidad de clusters: "<<C.size()<<endl;
        }
        else{
            C.erase(C.begin()+ encontrar_cluster_opt(C,c1));
            C_out.push_back(c1);
            //cout << "Agrego a C_out un cluster de tamano: "<<c1.s.size()<<endl;
            //cout << "Ahora C_out tiene una cantidad de clusters: "<<C_out.size()<<endl;
        }
    }
    //cout << "C_out cuando C tiene un solo elemento tiene tamano : "<< C_out.size()<<endl;
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
    //cout <<"la union de C_out y C tine tamano "<< size_union<<endl;
    Cluster_Puntos c_cp;
    //cout<<"cambiamos "<< c.m.x<<" , " <<c.m.y<< " por ";
    c.fusionar(cp);
    //cout << c.m.x<<" , " <<c.m.y<<endl;
    //cout << size_union <<endl;
    if (size_union > B){
        Cluster_Puntos c1;
        Cluster_Puntos c2;
        //cout<<"     entra a minmax"<<endl;
        tie(c1,c2) = min_max_split_opt(c);
        //dividir c en c1 y c2 usando minmax
        //cout << "los sets obtenidos con minmax son de tamanos "<< c1.size()<<" y "<<c2.size()<<endl;
        C_out.push_back(c1);
        C_out.push_back(c2);
    }
    //cout << "C_out final tiene tamano : "<< C_out.size()<<endl;
    //cout << "los 2 primeros sets son de tamnos "<< C_out[0].size()<<" y "<<C_out[1].size()<<endl;
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
    //cout <<"output interno recibe una cantidad de entries:"<< C_mra.size()<<endl;
    set<Point> C_in;
    set<Entry>::iterator i;
    for (i = C_mra.begin(); i!= C_mra.end(); i++){
        C_in.insert(i->p);
    }
    //cout <<"output interno recibe una cantidad de entries:"<< C_in.size()<<endl;
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
    //cout <<"output interno recibe una cantidad de entries:"<< C.size()<<endl;
    Mtree *A = new Mtree();
    Node *nodo = new Node();
    nodo->entries = C;
    //cout << "el nodo en output interno contiene "<<C.size()<<endl;
    A->root = nodo;
    return Entry(*G,R,A);
}


//retorna el mtree
Mtree AlgoritmoSS(set<Point> C_in){
    if (C_in.size() <= B){
        Entry *e = new Entry();
        *e = OutputHoja(C_in);
        //cout<< "("<<e->p.x<<","<<e->p.y<<") ";
        return *e->a;
    }
    //cout << "entra cluster de las hojas"<< endl;
    vector<set<Point>> C_out = Cluster2(C_in);
    //cout << "termina cluster de las hojas"<< endl;
    //cout << "se quieren hacer "<< C_out.size() << " nodos"<<endl;
    set<Entry> C;
    for (size_t i = 0; i < C_out.size(); i++){
        //
        set<Point> points = C_out[i];
        //cout << points.size()<< endl;
        set<Point>::iterator w;
        w = points.begin();
        //
        //cout<< "("<<w->x<<","<<w->y<<") ";
        Entry *e = new Entry();
        *e = OutputHoja(points);
        //cout<< "("<<e->cr<<") ";
        //cout<< "("<<e->p.x<<","<<e->p.y<<") ";
        C.insert(*e);
    }
    while (C.size() > B){
        C_in = {};
        set<Entry>::iterator j;
        for (j = C.begin(); j!= C.end(); j++){
            C_in.insert(j->p);
        }
        C_out = Cluster2(C_in);
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
    //cout<<e.p.x<<","<<e.p.y<<endl;
    return *e.a;
}

