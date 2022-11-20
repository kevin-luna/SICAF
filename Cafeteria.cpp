#pragma once
#include <string>
#include <limits>

#define READ std::ios::in
#define WRITE std::ios::out
#define APPEND std::ios::app
#define MAX_BUFF_SIZE std::numeric_limits<std::streamsize>::max()

template <typename T>
void validarEntrada(std::string mensajeError,T &var){
    while(1){
        if((std::cin>>var))break;
        std::cin.clear();
        std::cin.ignore(MAX_BUFF_SIZE, '\n');
        std::cout<<mensajeError;
    }
}

template <typename T>
void validarEntrada(std::string mensajeError,T &var,T limiteIzquierdo,T limiteDerecho){
    while(1){
        if((std::cin>>var) && var>=limiteIzquierdo && var<=limiteDerecho)break;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout<<mensajeError;
    }
}
// #include "MenuRegistroVentas.h"
// #include "SubmenuPedidos.h"

//ARCHIVOS
// bool buscarProductoEnPedido(int numeroMesa,std::string id){
//    for(Pedido &i:pedidosPorMesa[numeroMesa]){
//         if(i.producto.id==id){
//             std::cout<<"Ingrese la nueva cantidad: (i.cantidad)":<<"\n"
//             cin>>i.cantidad;
//             return true;
//         }
//     }
//     return false;
// }