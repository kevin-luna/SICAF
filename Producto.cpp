#pragma once
#include<iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "Cafeteria.cpp"
class Producto{
    public:
    std::string id;
    std::string nombre;
    float precio;

    Producto(){}
    Producto(std::string Id,std::string Nombre,float Precio){
        id=Id;
        nombre=Nombre;
        precio=Precio;
    }
    void leerProducto(){
        std::cout<<"Ingrese el nombre del producto: ";
        std::cin.ignore(MAX_BUFF_SIZE,'\n');
        std::getline(std::cin,nombre);
        std::cout<<"Ingrese el precio del producto: ";
        validarEntrada("Por favor ingrese un número con dos decimales.",precio);
        std::cout<<"Ingrese el identificador (ID) del producto: ";
        validarEntrada("Por favor ingrese un código de producto sin espacios.",id);
    }
    void guardarProducto(std::fstream &archivo){
        archivo<<id<<";"<<nombre<<";"<<std::fixed<<std::setprecision(2)<<precio<<";";
    }

    std::string obtenerId(){return id;}
    std::string obtenerNombre(){return nombre;}
    float obtenerPrecio(){return precio;}
};

