#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <limits>
#include <map>
#include <list>
#include "Producto.cpp"
#include "Pedido.cpp"
#include "Cafeteria.cpp"
#include "CatalogoProductos.cpp"
class Menu{
    private:
    bool salir=false;
    public:
    static std::time_t t;//obtiene la fecha actual
    static std::tm* fechaActual;
    static std::string textoFechaActual;
    static CatalogoProductos miCatalogo;
    UI cantidadOpciones;
    UI opcionLeida;
    
    Menu(){
        textoFechaActual=std::to_string(fechaActual->tm_mday)+"/"+std::to_string(fechaActual->tm_mon)+"/"+std::to_string(fechaActual->tm_year+1900);
    }

    void leerOpcion(){
        validarEntrada("Introduzca una opcion valida\n",opcionLeida,static_cast<UI>(1),cantidadOpciones);
        seleccionarOpcion(opcionLeida);
    }
    virtual void seleccionarOpcion(int op)=0;
    virtual void mostrarMenu()=0;
    void iniciar(){
        while(!salir){
            mostrarMenu();
            leerOpcion();
        }
    }
    void cerrar(){
        salir=true;
    }
};

CatalogoProductos Menu::miCatalogo;
std::time_t Menu::t = std::time(0);//obtiene la fecha actual
std::tm* Menu::fechaActual = std::localtime(&t);
std::string Menu::textoFechaActual;