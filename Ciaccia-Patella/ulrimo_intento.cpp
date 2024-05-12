// A divide and conquer program in C++ to find the smallest dist_euance from a
// given set of points.
 
#include <iostream>
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "auxfun_ss.cpp"


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
 
/* Following two functions are needed for library function qsort().

   Refer: http://www.cplusplus.com/reference/clibrary/cstdlib/qsort/ */
 
// Needed to sort array of points according to X coordinate

#include <vector>
using namespace std;

void swap(vector<Cluster_Puntos> &v, int x, int y) {
    Cluster_Puntos temp = v[x];
    v[x] = v[y];
    v[y] = temp;
}

void quicksortx(vector<Cluster_Puntos> &vec, int L, int R) {
    //cout << "entra a qsortx"<<endl;
    int i, j, mid;
    double piv;
    i = L;
    j = R;
    mid = L + (R - L) / 2;
    piv = vec[mid].m.x;
    //cout << "asigna valores"<<endl;
    while (i<R || j>L) {
        while (vec[i].m.x < piv)
            i++;
        while (vec[j].m.x > piv)
            j--;

        if (i <= j) {
            swap(vec, i, j); //error=swap function doesnt take 3 arguments
            //cout<<"successfull swaap"<<endl;
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
    //cout << "termina while"<<endl;
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
            swap(vec, i, j); //error=swap function doesnt take 3 arguments
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

// A utility function to find the dist_euance between two points

// double dist_eu(Point p1, Point p2)
// {

//     return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +

//                  (p1.y - p2.y)*(p1.y - p2.y)

//                );
// }
 
// A Brute Force method to return the smallest dist_euance between two points
// in P[] of size n

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
    //cout << "Los clusters mas cercanos tienen tamanos "<<c1.s.size()<<" y "<<c2.s.size()<< endl;
    return make_tuple(c1,c2,min);
}

tuple<Cluster_Puntos, Cluster_Puntos, double> stripClosest(vector<Cluster_Puntos> strip, int size, double d, Cluster_Puntos ca, Cluster_Puntos cb){

    double min = d;  // Initialize the minimum dist_euance as d
    Cluster_Puntos c1=ca;
    Cluster_Puntos c2=cb;

    // Pick all points one by one and try the next points till the difference

    // between y coordinates is smaller than d.

    // This is a proven fact that this loop runs at most 6 times

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

    //cout << "la d min encontrada en stripClosest es "<<min<<endl;
    //cout << "Los clusters mas cercanos tienen tamanos "<<c1.s.size()<<" y "<<c2.s.size()<< endl;

    return make_tuple(c1,c2,min);
}
 
// A recursive function to find the smallest dist_euance. The array Px contains
// all points sorted according to x coordinates and Py contains all points
// sorted according to y coordinates

tuple<Cluster_Puntos, Cluster_Puntos, double>closestUtil(vector<Cluster_Puntos> Px, vector<Cluster_Puntos> Py, int n){

    // If there are 2 or 3 points, then use brute force
    if (n <= 3)

        return bruteForce(Px, n);
 

    // Find the middle point

    int mid = n/2;

    Cluster_Puntos midPoint = Px[mid];
 

    // Divide points in y sorted array around the vertical line.

    // Assumption: All x coordinates are dist_euinct.

    vector<Cluster_Puntos> Pyl;   // y sorted points on left of vertical line

    vector<Cluster_Puntos> Pyr;  // y sorted points on right of vertical line
     // indexes of left and right subarrays
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
 

    // Consider the vertical line passing through the middle point

    // calculate the smallest dist_euance dl on left of middle point and

    // dr on right side
    vector<Cluster_Puntos> P_l;
    for(int a = 0; a<mid; a++){
        P_l.push_back(Px[a]);
    }
    //cout << "entra a llamada a closest Util izq con #elementos "<<mid<<endl;
    Cluster_Puntos c1l;
    Cluster_Puntos c2l;
    double dl;
    tie(c1l,c2l,dl) = closestUtil(P_l, Pyl, P_l.size());
    //cout << "pasa llamada a closest Util der obteniendo "<<dl<<endl;
    vector<Cluster_Puntos> P_r;
    for(int z = mid; z<n; z++){
        P_r.push_back(Px[z]);
    }
    //cout << "entra a llamada a closest Util der con #elementos "<<n-mid<<endl;
    Cluster_Puntos c1r;
    Cluster_Puntos c2r;
    double dr;
    tie(c1r,c2r,dr)= closestUtil(P_r, Pyr, P_r.size());
    //cout << "pasa llamada a closest Util der obteniendo "<<dr<<endl;
 

    // Find the smaller of two dist_euances
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
 

    // Build an array strip[] that contains points close (closer than d)

    // to the line passing through the middle point

    vector<Cluster_Puntos> strip;
    int j=0;
    for (int w = 0; w < n; w++){
       if (abs(Py[w].m.x - midPoint.m.x) < d){
            strip.push_back(Py[w]);
            j++;
        } 
    }

    // Find the closest points in strip.  Return the minimum of d and closest

    // dist_euance is strip[]

    return stripClosest(strip, j, d,c1m,c2m);
}
 
// The main function that finds the smallest dist_euance
// This method mainly uses closestUtil()

tuple<Cluster_Puntos,Cluster_Puntos> closest(vector<Cluster_Puntos> P){
    vector<Cluster_Puntos> Px;

    vector<Cluster_Puntos> Py;

    int n = P.size();
    //cout <<n<<endl;

    for (size_t i = 0; i < n; i++){
        Px.push_back(P[i]);
        Py.push_back(P[i]);
    }
 
    //cout<< "comienza qsortx con Px tamano "<<Px.size()<<endl;
    //qsort(&Px, n, sizeof(Point), compareX);
    quicksortx(Px, 0, n-1);
    //cout<< "comienza qsorty"<<endl;
    //qsort(&Py, n, sizeof(Point), compareY);
    quicksorty(Py, 0, n-1);

    // Use recursive function closestUtil() to find the smallest dist_euance
    //cout << "llamo closestUyil con"<<Px.size()<< endl;
    Cluster_Puntos c1;
    Cluster_Puntos c2;
    double d;
    tie(c1,c2,d) = closestUtil(Px, Py, n);
    //cout << "Los clusters mas cercanos tienen tamanos "<<c1.s.size()<<" y "<<c2.s.size()<< endl;

    return make_tuple(c1,c2);
}