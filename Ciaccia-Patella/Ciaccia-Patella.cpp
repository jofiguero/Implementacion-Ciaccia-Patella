#include <stdio.h>
#include <stdlib.h>
#include "Aux-Functions.cpp"
#include "Aux-Clases.cpp"
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std; 

Mtree *CP(vector<Point>& setp){
    //calculamos B, b y el tamaño del set
    int B = 4096/sizeof(Entry);
    int b = B/2;
    int size = setp.size();

    printf("el tamaño del conjunto recibido es %d\n", size);
    //Si |P|<= B, creamos un arbol t, insertamos los puntos y lo retornamos
    if(size <= B){
        printf("soy mas chiquito\n");
        Node* nodo_hoja = new Node;
        for(Point punto : setp){
            Entry entrada; 
            entrada.p =punto;
            entrada.cr =0;
            entrada.a =NULL;
            nodo_hoja->entries.insert(entrada);
        }
        Mtree* arbol = new Mtree(nodo_hoja);
        return arbol;
    }

    //Se crea el set que contendrá todos los conjuntos de puntos con sus representantes
    vector<Conjunto_sample> conjuntos;

    //Se crea el conjunto de todos los samples
    vector<Point> F;

    int k;
    do{
        //Nos aseguramos de que conjuntos y F esten vacios
        conjuntos.clear();
        F.clear();

        // Se toman los primeros min(B,n/B) puntos para formar el arreglo F de samples
        k = std::min(B,(int)ceil(size/(double)B)); 
        F = setAleatorio(setp,k);

        //Se inicializan todos los conjuntos de puntos y se añaden al set de conjuntos
        for(Point& punto: F){
            Conjunto_sample conjunto =  Conjunto_sample(punto);
            conjuntos.push_back(conjunto);
        }
        //Se ingresan los puntos del set a los conjuntos
        for(Point punto: setp){
            Point mas_cercano = closer(F,punto);
            for (Conjunto_sample& conjunto: conjuntos) {
                if (conjunto.sample == mas_cercano) {
                    conjunto.agregarPunto(punto);
                    //printf("el tamano de este conjunto es %d\n",conjunto.conjunto.size());
                }
            }
        }
        
        //Etapa de redistribucion
        //Para cada conjunto en el set de conjuntos
        for(Conjunto_sample& conjunto: conjuntos){
            //Si es que el tamaño del conjunto es menos a b
            if(conjunto.conjunto.size() < b){
                //Eliminamos su representante de F
                Point representante = conjunto.sample;
                F.erase(find(F.begin(), F.end(), representante));
                
                //Para cada punto en el conjunto a desmembrar
                for(Point& punto:conjunto.conjunto){
                    //Buscamos el sample mas cercano en F y lo introducimos a su conjunto
                    Point mas_cercano = closer(F,punto);
                    for (Conjunto_sample& conjuntoN: conjuntos) {
                        if (conjuntoN.sample == mas_cercano && conjuntoN != conjunto) {
                            conjuntoN.agregarPunto(punto);
                        }
                    }
                    
                }
                conjuntos.erase(find(conjuntos.begin(), conjuntos.end(), conjunto));
            }
        }
    }while(F.size()<=1);
    printf("k = %d\n",k);
    printf("Los puntos escogidos son:\n");
    for(Point p: F){
        printf("%f,%f\n",p.x,p.y);
    }
    //Creamos un vector de AS cuyos arboles se obtendrán de aplicar el algoritmo sobre los conjuntos
    vector<AS*> ASs;
    printf("Paso recursivo\n\n");
    //Paso recursivo
    for(Conjunto_sample conjunto: conjuntos){
        printf("alo\n");
        Point& sample = conjunto.sample;
        printf("Los puntos que va a recibir el cp son:\n");
        for(Point p: conjunto.conjunto){
            printf("%f,%f\n",p.x,p.y);
        }
        Mtree* arbol = CP(conjunto.conjunto);
        printf("\nVolvi del paso recursivo\n");
        AS * arbolSample = new AS(sample,arbol);
        printf("El tamaño del conjunto ASs antes de push %d\n",ASs.size());
        ASs.push_back(arbolSample);
        printf("El tamaño del conjunto ASs despues de push %d\n",ASs.size());
    }
    printf("Reordenamiento de raices\n\n");
    printf("El tamaño del conjunto ASs es %d\n",ASs.size());
    //Reordenamiento de raices
    for(AS* as: ASs){
        printf("d1\n");
        Mtree *arbol = as->arbol;
        printf("d1.5\n");
        Node *ptr_nodo_raiz = arbol->root;
        printf("d1.6\n");
        Node nodo_raiz = *ptr_nodo_raiz;
        printf("d1.7\n");
        set<Entry> entradas = nodo_raiz.entries;
        printf("El tamaño de las entradas es %d\n",entradas.size());
        Point sample = as->sample;
        printf("d2\n");

        if(entradas.size()<b){
            printf("d3\n");
            ASs.erase(find(ASs.begin(), ASs.end(), as));
            printf("d4\n");
            F.erase(find(F.begin(), F.end(), sample));
            printf("d5\n");
            for(Entry entrada: entradas){
                printf("d6\n");
                AS*  newAS = new AS(entrada.p,entrada.a);
                printf("d7\n");
                ASs.push_back(newAS);
                printf("d8\n");
                F.push_back(entrada.p);
                printf("d9\n");
            }
        }
    }
    printf("Calculo de altura\n\n");
    printf("El tamaño del conjunto ASs es %d\n",ASs.size());
    //Calculamos h para balancear
    int h = alturaMinima(ASs);
    printf("La altura minima es%d\n",h);
    //Inicializamos Tprima (será el representante de T')
    vector<AS*> Tprima;
    printf("Balanceamiento\n\n");
    //Etapa de balanceamiento
    for(AS* as: ASs){
        int alturaArbol = altura(as->arbol);
        if(alturaArbol == h){
            Tprima.push_back(as);
        }else{
            Point representante = as->sample;
            F.erase(find(F.begin(), F.end(), representante));

            set<Entry> entradas = as->arbol->root->entries;

            SubarbolesValidos(as->arbol, as->sample, Tprima, F, h);
        }
    }
    printf("Creacion de Tsup\n\n");
    //Definimos Tsup
    Mtree* Tsup = CP(F);
    printf("Unir Tsup con T'\n\n");
    //Unimos Tsup con los arboles de Tprima
    for(AS* as: ASs){
        /*Usamos la funcion unirArboles entregandole el arbol inferior (Tinf), el sample (sample)
        y un puntero al nodo raiz de Tsup para que comience su busqueda*/
        unirArboles(as->arbol,as->sample,Tsup);
    }

    printf("Calculo de radios cobertores\n\n");
    //Rellenamos los radios cobertores
    cr(Tsup->root);

    return Tsup;
}

