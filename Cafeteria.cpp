#pragma once
#include <string>
#include <limits>
#include <iostream>

//este archivo proporciona algunas abreviaturas y funciones
//útiles para el proyecto

//abreviaturas
#define READ std::ios::in
#define WRITE std::ios::out
#define APPEND std::ios::app
#define MAX_BUFF_SIZE std::numeric_limits<std::streamsize>::max()
typedef unsigned int UI;


//las funciones sobrecargadas validarEntrada, proporcionan una interfaz
//para leer información desde la consola, de forma segura, ya
//que siempre asegura que el tipo de dato leido sea el requerido,
//y de ser necesario, que se encuentre dentro de un límite establecido
//para ahorrar código, se crearon las funciones utilizando templates,
//de esta manera generalizamos la misma lógica para distintos tipos de datos 

//ambas funciones reciben como parámetro el mensaje de error a mostrar en caso de
//no leer el valor correcto y una referencia a la variable donde se almacenará
//la información leída

template <typename T>
void validarEntrada(std::string mensajeError,T &var){
    while(1){
        if((std::cin>>var))break;//si la lectura fue satisfactoria termina el bucle
        //si no, entonces limpia el flujo, elimina todos los caracteres
        //de nueva línea que quedaron dentro del flujo e imprime
        //el mensaje de error
        std::cin.clear();
        std::cin.ignore(MAX_BUFF_SIZE, '\n');
        std::cout<<mensajeError;
    }
}
//para la segunda función sobrecargada, también pasamos como parámetro
//el intervalo dentro del cual debe estar comprendido el valor que esperamos
template <typename T>
void validarEntrada(std::string mensajeError,T &var,T limiteIzquierdo,T limiteDerecho){
    while(1){
        if((std::cin>>var) && var>=limiteIzquierdo && var<=limiteDerecho)break;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout<<mensajeError;
    }
}
