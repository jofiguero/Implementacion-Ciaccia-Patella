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
    Node *a;
} Entry;

typedef struct{
    int sample;
    double *point;
    int count;
} Samples;

int main(){
    printf(siezeof(Entry))
    return 0;
}