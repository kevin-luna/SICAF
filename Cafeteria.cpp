#pragma once
#include <string>
#include <limits>
#include <iostream>

#define READ std::ios::in
#define WRITE std::ios::out
#define APPEND std::ios::app
#define MAX_BUFF_SIZE std::numeric_limits<std::streamsize>::max()
typedef unsigned int UI;

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
