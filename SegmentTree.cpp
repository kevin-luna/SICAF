#include <vector>
#include <algorithm>
#include "Cafeteria.cpp"
class SegmentTree{
    public:
    //vector que almacena las sumas contenidas en cada nodo
    std::vector<float> arbol;
    //vector que almacena la lista de valores orignal
    std::vector<float> valores;
    //calculo de hijo izquierdo y derecho de un nodo
    int izq(int n){return n*2;}
    int der(int n){return n*2+1;}
    //almacena una copia de los valores originales del arreglo
    //y comienza a construir el árbol
    SegmentTree(std::vector<float> &arreglo){
        valores=arreglo;
        arbol.assign(4*(valores.size()),0);
        construir(1,0,valores.size()-1);
    }
    //vacía los vectores
    void limpiar(){
        for(auto e:arbol)e=0;
        for(auto e:valores)e=0;
    }

    //recorre todo el árbol y rellena cada nodo con la suma
    //de los valores contenidos en el segmento [l,r]
    void construir(int nodo,int limiteIzquierdo,int limiteDerecho){
        if(limiteIzquierdo==limiteDerecho) arbol[nodo]=valores[limiteIzquierdo];
        else{
            int m=(limiteIzquierdo+limiteDerecho)/2;
            construir(izq(nodo),limiteIzquierdo,m);
            construir(der(nodo),m+1,limiteDerecho);
            arbol[nodo]=arbol[izq(nodo)]+arbol[der(nodo)];
        }
    }

    //método sobrecargado que devuelve la suma dentro de un rango [l,r]
    float consultaSuma(int izq,int der){
        return consultaSuma(1,0,valores.size()-1,izq,der);
    }
    //método que devuelve la suma dentro de un rango
    float consultaSuma(int nodo,int limiteIzquierdo,int limiteDerecho,int sumaIzquierda,int sumaDerecha){
        // si el rango especificado es invalido, retorna
        if(sumaDerecha<sumaIzquierda)return 0;
        //si el límite izquierdo del segmento que queremos sumar
        //es igual al límite izquierdo del segmento actual
        //retorna la suma almacenada en ese nodo
        if(limiteIzquierdo==sumaIzquierda && limiteDerecho==sumaDerecha) return arbol[nodo];
        //si no, entonces sigue buscando la suma en los nodos hijos
        int m=(limiteIzquierdo+limiteDerecho)/2;
        return consultaSuma(izq(nodo),limiteIzquierdo,m,sumaIzquierda,std::min(m,sumaDerecha))
        +consultaSuma(der(nodo),m+1,limiteDerecho,std::max(m+1,sumaIzquierda),sumaDerecha);
    }
};