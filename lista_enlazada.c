#include <stdio.h>
#include <stdlib.h>
//#include "structures.c"

typedef struct nodoPuntos{
    int punto;
    struct nodoPuntos *sgte;
}NodoPuntos;

NodoPuntos* inicioListaPuntos(){
    NodoPuntos *nodo = (NodoPuntos*)malloc((sizeof(NodoPuntos)));
    nodo->sgte = NULL;
    nodo->punto = NULL;
    return nodo;
}

void appendPunto(NodoPuntos *lista, int p){
    NodoPuntos *nodo = (NodoPuntos*)malloc((sizeof(NodoPuntos)));
    nodo -> sgte = NULL;
    nodo -> punto = p;
    NodoPuntos * pointer = lista;
    while (pointer->punto != NULL){
        pointer = pointer->sgte;
    }
    pointer->sgte    = nodo; 

}

void ver(NodoPuntos* n){
    NodoPuntos * pointer = n;
    while(pointer != NULL){
        printf("%d\n",pointer->punto);
        pointer = pointer->sgte;
    }
}

int main(){
    NodoPuntos *n = inicioListaPuntos();
    appendPunto(n,2);
    appendPunto(n,3);
    appendPunto(n,7);
    appendPunto(n,1);
    ver(n);
}

