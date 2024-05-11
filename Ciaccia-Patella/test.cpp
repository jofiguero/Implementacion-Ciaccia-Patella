#include <stdio.h>
#include <stdlib.h>
#include "Aux-Clases.cpp"
#include "Aux-Functions.cpp"
#include "Ciaccia-Patella.cpp"
#include <set>

using namespace std; 

int main(){
    
    Point p1;
    Point p2;
    Point p3;
    Point p4;
    Point p5;
    Point p6;
    Point p7;
    Point p8;
    Point p9;
    Point p10;
    Point p11;

    p1.x = 2;
    p1.y = 3;
    p2.x = 1;
    p2.y = 2;
    p3.x = 3;
    p3.y = 4;
    p4.x = 1;
    p4.y = 0;
    p5.x = 2;
    p5.y = 8;
    p6.x = 3;
    p6.y = 8;
    p7.x = 5;
    p7.y = 8;
    p8.x = 2;
    p8.y = 2;
    p9.x = 3;
    p9.y = 3;
    p10.x = 4;
    p10.y = 0;
    p11.x = 6;
    p11.y = 7;

    Mtree t1;
    Mtree t2;
    Mtree t3;
    Mtree t4;
    Mtree t5;
    Mtree t6;
    Mtree t7;

    Entry e1;
    Entry e2;
    Entry e3;
    Entry e4;
    Entry e5;
    Entry e6;
    Entry e7;
    Entry e8;
    Entry e9;
    Entry e10;
    Entry e11;
    Entry e12;
    Entry e13;
    Entry e14;
    Entry e15;
    Entry e16;
    Entry e17;

    e1.p = p1;
    e1.cr = 0;
    e1.a = NULL;
    e2.p = p2;
    e2.cr = 0;
    e2.a = NULL;
    e3.p = p3;
    e3.cr = 0;
    e3.a = NULL;
    e4.p = p4;
    e4.cr = 0;
    e4.a = NULL;
    e5.p = p5;
    e5.cr = 0;
    e5.a = NULL;
    e6.p = p6;
    e6.cr = 0;
    e6.a = NULL;
    e7.p = p7;
    e7.cr = 0;
    e7.a = NULL;
    e8.p = p8;
    e8.cr = 0;
    e8.a = NULL;
    e9.p = p9;
    e9.cr = 0;
    e9.a = NULL;
    e10.p = p10;
    e10.cr = 0;
    e10.a = NULL;
    e11.p = p11;
    e11.cr = 0;
    e11.a = NULL;
    e12.p = p1;
    e12.cr = 0;
    e12.a = &t5;
    e13.p = p3;
    e13.cr = 0;
    e13.a = &t6;
    e14.p = p4;
    e14.cr = 0;
    e14.a = &t7;
    e15.p = p3;
    e15.cr = 0;
    e15.a = &t2;
    e16.p = p7;
    e16.cr = 0;
    e16.a = &t3;
    e17.p = p11;
    e17.cr = 0;
    e17.a = &t4;

    set<Entry> se1;
    set<Entry> se2;
    set<Entry> se3;
    set<Entry> se4;
    set<Entry> se5;
    set<Entry> se6;
    set<Entry> se7;

    se1.insert(e15);
    se1.insert(e16);
    se1.insert(e17);

    se2.insert(e12);
    se2.insert(e13);
    se2.insert(e14);

    se3.insert(e6);
    se3.insert(e7);
    se3.insert(e8);

    se4.insert(e9);
    se4.insert(e10);
    se4.insert(e11);

    se5.insert(e1);
    se5.insert(e2);

    se6.insert(e3);

    se7.insert(e4);
    se7.insert(e5);

    Node n1;
    Node n2;
    Node n3;
    Node n4;
    Node n5;
    Node n6;
    Node n7;

    n1.entries = se1;
    n2.entries = se2;
    n3.entries = se3;
    n4.entries = se4;
    n5.entries = se5;
    n6.entries = se6;
    n7.entries = se7;

    t1.root = &n1;
    t2.root = &n2;
    t3.root = &n3;
    t4.root = &n4;
    t5.root = &n5;
    t6.root = &n6;
    t7.root = &n7;

    Mtree* arbol = new Mtree(CP(conjunto.conjunto));


    ImprimeArbol2(t1);

    printf("La altura del arbol es %d\n",altura(&t1));

    
    

}

