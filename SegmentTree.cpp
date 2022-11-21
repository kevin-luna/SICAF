#include <vector>
#include <algorithm>
#include "Cafeteria.cpp"
class SegmentTree{
    public:
    std::vector<float> arbol;
    std::vector<float> valores;
    int izq(int n){return n*2;}
    int der(int n){return n*2+1;}
    SegmentTree(std::vector<float> &arreglo){
        valores=arreglo;
        arbol.assign(4*(valores.size()),0);
        construir(1,0,valores.size()-1);
    }

    void limpiar(){
        for(auto e:arbol)e=0;
        for(auto e:valores)e=0;
    }

    void construir(int nodo,int limiteIzquierdo,int limiteDerecho){
        if(limiteIzquierdo==limiteDerecho) arbol[nodo]=valores[limiteIzquierdo];
        else{
            int m=(limiteIzquierdo+limiteDerecho)/2;
            construir(izq(nodo),limiteIzquierdo,m);
            construir(der(nodo),m+1,limiteDerecho);
            arbol[nodo]=arbol[izq(nodo)]+arbol[der(nodo)];
        }
    }

    float consultaSuma(int izq,int der){
        return consultaSuma(1,0,valores.size()-1,izq,der);
    }

    float consultaSuma(int nodo,int limiteIzquierdo,int limiteDerecho,int sumaIzquierda,int sumaDerecha){
        if(sumaDerecha<sumaIzquierda)return 0;
        if(limiteIzquierdo==sumaIzquierda && limiteDerecho==sumaDerecha) return arbol[nodo];
        int m=(limiteIzquierdo+limiteDerecho)/2;
        return consultaSuma(izq(nodo),limiteIzquierdo,m,sumaIzquierda,std::min(m,sumaDerecha))
        +consultaSuma(der(nodo),m+1,limiteDerecho,std::max(m+1,sumaIzquierda),sumaDerecha);
    }

    void imprimir(){
        for(auto i:arbol)std::cout<<i<<" ";
    }
};

// int main(){
//     std::vector<float> a = {1.0,2.0,3.0,4.0,5.0,6.0,7.0};
//     SegmentTree tree(a);
//     // tree.imprimir();
//     std::cout<<tree.consultaSuma(0,6);
// };