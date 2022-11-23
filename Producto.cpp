#pragma once
#include<iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "Cafeteria.cpp"
class Producto{
    public:
    //datos del producto
    std::string id;
    std::string nombre;
    float precio;
    //constructor por defecto
    Producto(){}
    //constructor de la clase
    Producto(std::string Id,std::string Nombre,float Precio){
        id=Id;
        nombre=Nombre;
        precio=Precio;
    }
    //dentro de este método se lee a través de la consola la información para rellenar
    //los atributos del objeto pedido
    void leerProducto(){
        std::cout<<"Ingrese el nombre del producto: ";
        std::cin.ignore(MAX_BUFF_SIZE,'\n');
        std::getline(std::cin,nombre);
        std::cout<<"Ingrese el precio del producto: ";
        validarEntrada("Por favor ingrese un número con dos decimales.",precio);
        std::cout<<"Ingrese el identificador (ID) del producto: ";
        validarEntrada("Por favor ingrese un código de producto sin espacios.",id);
    }
    //este método recibe como parámetro un flujo de archivo y escribe
    //en él los datos del producto
    void guardarProducto(std::fstream &archivo){
        archivo<<id<<";"<<nombre<<";"<<std::fixed<<std::setprecision(2)<<precio<<";";
    }

};

