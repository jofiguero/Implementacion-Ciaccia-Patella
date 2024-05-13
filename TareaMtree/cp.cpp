#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include "par_cercano_ss.cpp"

using namespace std; 

Mtree *CP(vector<Point>& setp){
    //calculamos B, b y el tamaño del set
    int B = 4096/sizeof(Entry);
    int b = B/2;
    int size = setp.size();
    //Si |P|<= B, creamos un arbol t, insertamos los puntos y lo retornamos
    if(size <= B){ 
        Node* nodo_hoja = new Node();
        for(Point punto : setp){
            Entry *entrada = new Entry(punto);
            nodo_hoja->entries.insert(*entrada);
        }
        Mtree* arbol = new Mtree(nodo_hoja);
        return arbol;
    }

    //Se crea el set que contendrá todos los conjuntos de puntos con sus representantes
    vector<Conjunto_sample*> conjuntos;

    //Se crea el conjunto de todos los samples
    vector<Point> F;

    int k;
    int i = 0;
    do{
        //Nos aseguramos de que conjuntos y F esten vacios
        conjuntos.clear();
        F.clear();
        // Se toman los primeros min(B,n/B) puntos para formar el arreglo F de samples
        k = std::min(B,(int)ceil(size/(double)B)); 
        F = setAleatorio(setp,k,i);
        //Se inicializan todos los conjuntos de puntos y se añaden al set de conjuntos
        for(Point punto: F){
            Conjunto_sample* conjunto =  new Conjunto_sample(punto);
            conjuntos.push_back(conjunto);
        }
        //Se ingresan los puntos del set a los conjuntos
        for(Point punto: setp){ 
            Point mas_cercano = closer(F,punto);
            for (Conjunto_sample *conjunto: conjuntos) {
                if (conjunto->sample == mas_cercano) {
                    auto it = std::find(conjunto->conjunto.begin(), conjunto->conjunto.end(), punto);
                    if (it == conjunto->conjunto.end()) {
                        conjunto->agregarPunto(punto);
                    }
                    
                }
            }
        }
        
        //Etapa de redistribucion
        for(auto it = conjuntos.begin(); it != conjuntos.end(); ) {
            Conjunto_sample *conjunto = *it;
            // Si el tamaño del conjunto es menor que b
            if(conjunto->conjunto.size() < b) {
                // Eliminamos su representante de F
                F.erase(find(F.begin(), F.end(), conjunto->sample));
                // Para cada punto en el conjunto a desmembrar
                for(Point& punto : conjunto->conjunto) {
                    // Buscamos el sample más cercano en F y lo introducimos a su conjunto
                    Point mas_cercano = closer(F,punto);
                    for(auto& conjuntoN : conjuntos) {
                        if(conjuntoN->sample == mas_cercano && conjuntoN != conjunto) {
                            conjuntoN->agregarPunto(punto);
                        }
                    }
                }
                it = conjuntos.erase(it); // Eliminar el elemento y actualizar el iterador
            } else {
                ++it; // Si no se elimina, avanzamos al siguiente elemento
            }
        }
        i++;
    }while(F.size()==1);
    //Creamos un vector de AS cuyos arboles se obtendrán de aplicar el algoritmo sobre los conjuntos
    vector<AS*> ASs;
    //Paso recursivo
    
    for(Conjunto_sample *conjunto: conjuntos){
        //Point sample = conjunto->sample;
        //Mtree* arbol = CP(conjunto->conjunto);
        AS * arbolSample = new AS(conjunto->sample,CP(conjunto->conjunto));
        ASs.push_back(arbolSample);
    };
    //Reordenamiento de raices
    for(AS* as: ASs){
        if(as->arbol->root->entries.size()<b){
            ASs.erase(find(ASs.begin(), ASs.end(), as));
            F.erase(find(F.begin(), F.end(), as->sample));
            for(Entry entrada: as->arbol->root->entries){
                //Mtree *newTree = new Mtree(entrada.a->root);
                AS*  newAS = new AS(entrada.p,entrada.a);
                ASs.push_back(newAS);
                F.push_back(entrada.p);
            }
        }
    }
    //Calculamos h para balancear
    int h = alturaMinima(ASs);
    //Inicializamos Tprima (será el representante de T')
    vector<AS*> Tprima;
    //Etapa de balanceamiento
    for(AS*& as: ASs){
        if(altura(as->arbol) == h){
            Tprima.push_back(as);
        }else{
            Point representante = as->sample;
            F.erase(find(F.begin(), F.end(), representante));
            SubarbolesValidos(as->arbol, as->sample, &Tprima, &F, h);
        }
    }
    Mtree* Tsup = CP(F);
    //Unimos Tsup con los arboles de Tprima
    for(AS* as: Tprima){
        /*Usamos la funcion unirArboles entregandole el arbol inferior (Tinf), el sample (sample)
        y un puntero al nodo raiz de Tsup para que comience su busqueda*/
        unirArboles(as->arbol,as->sample,Tsup);
    }
    for(AS* as: ASs){
        delete as;
    }
    for(Conjunto_sample* cs: conjuntos){
        delete cs;
    }
    //Rellenamos los radios cobertores
    cr(Tsup->root);
    return Tsup;
}

