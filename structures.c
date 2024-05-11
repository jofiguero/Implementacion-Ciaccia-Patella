#include <stdio.h>
#include <stdlib.h>

typedef struct{
    Node *root;
} Tree;

typedef struct{
    double x;
    double y;
}Point;

typedef struct{
    Entry *List;
    int count;
} Node;

typedef struct {
    Point p;
    double cr;
    Tree *a;
} Entry;

typedef struct{
    Node *root;
} Tree;

int main(){
    printf("%lu",sizeof(Entry));
    return 0;
}
