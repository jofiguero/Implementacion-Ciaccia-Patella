#include <iostream>
#include <stdio.h>
using namespace std;
#include <set>

class Point{
    public:
    double x;
    double y;

    Point (double x, double y): x(x), y(y){}
    Point(){}
};

inline bool operator<(const Point& lhs, const Point& rhs){
    if (lhs.x != rhs.x){
        return lhs.x < rhs.x; 
    }
    else{
        return lhs.y < rhs.y;
    }
}
inline bool operator==(const Point& p1, const Point& p2)  {
    return p1.x == p2.x && p1.y == p2.y;
}

class Query{
    public:
    Point q;
    double r;

    Query (Point q, double r): q(q), r(r){}
 };

class Entry{
    public:
    Point p;
    double cr;
    class Mtree *a;

    Entry(Point p, double cr, Mtree *a): p(p), cr(cr), a(a){}
    Entry(Point p): p(p), cr(NULL), a(NULL){}
    Entry(){}
};

inline bool operator<(const Entry& lhs, const Entry& rhs){
  return lhs.p < rhs.p;
}
inline bool operator==(const Entry& e1, const Entry& e2)  {
    return e1.p.x == e2.p.x && e1.p.y == e2.p.y && e1.cr == e2.cr && e1.a == e2.a;
}

class Node{
    public:
    set <Entry> entries;
    Node(set<Entry> e): entries(e){}
    Node(){}
};

class Mtree{
    public:
    Node *root;
};

class MtreeIdeal{
    public:
    Node root;
};

class EntryIdeal{
    public:
    Point p;
    double cr;
    class MtreeIdeal *a;

    EntryIdeal(Point p, double cr, MtreeIdeal *a): p(p), cr(cr), a(a){}
    EntryIdeal(Point p): p(p), cr(NULL), a(NULL){}
    EntryIdeal(){}
};

inline bool operator<(const EntryIdeal& lhs, const EntryIdeal& rhs){
  return lhs.p < rhs.p;
}
inline bool operator==(const EntryIdeal& e1, const EntryIdeal& e2)  {
    return e1.p.x == e2.p.x && e1.p.y == e2.p.y && e1.cr == e2.cr && e1.a == e2.a;
}