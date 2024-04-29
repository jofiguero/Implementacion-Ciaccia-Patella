#include <stdio.h>
#include <stdlib.h>

void CP(Point *point, int count, int B){
    //Si |P|<= B, creamos un arbol t, insertamos los puntos y lo retornamos
    if(count <= B){
        Entry *list =(Entry *) malloc(sizeof(Entry)*B);
        Node n = {list,count};
        for(i = 0; i<count; i++){
            put(&n, *(point+i), NULL, NULL);
        }
        Tree t= &n;
        return t;
    }
    // Se toman los primeros min(B,n/B) puntos para formar el arreglo F de samples
    int k = min(B,count/B); 
    int F[k];
    for(i = 0; i<k;i++){
        F[i] = *(point+i);
    }
}