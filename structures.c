#include <stdio.h>
#include <stdlib.h>

typedef struct{
    Entry *list;
    int count;
} Node;

typedef struct {
    double p;
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