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
    Point F[k];
    
    for(int i = 0; i<k;i++){
        F[i] = *(point+i);
    }

    Par_samples ListaPares[count];
    for(int i = 0; i<count; i++){
        Point punto = *(point+i);
        Point mas_cercano = closer(&F,k,punto);
        Par_sample par = {punto,mas_cercano};
        ListaPares[i] = par;
    }

    Conjunto_sample *lista_conjuntos = (Conjunto_sample *) malloc(sizeof(Conjunto_sample)*k)
    for(int i = 0; i<k;i++){
        lista_conjuntos[i].sample = F[i];
        lista_conjuntos[i].count =  0;
    }

    
}