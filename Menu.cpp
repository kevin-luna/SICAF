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
//esta será la clase padre que define el comportamiento de todos
//los menús, a su vez todos los tipos de menú heredan de ella
class Menu{
    private:
    bool salir=false;//Esta variable controla la salida del menú. Si está en true, el menú se cerrará.
    public:
    //objetos estáticos disponibles para todos los menús
    static std::time_t t;//obtiene la fecha actual
    static std::tm* fechaActual;//este objeto permitirá extraer los datos de la fecha actual
    static std::string textoFechaActual;//este string almacenará la fecha actual del sistema en texto plano.
    static CatalogoProductos miCatalogo;//controlador para el catálogo de productos
    UI cantidadOpciones;//la cantidad total de opciones disponibles en un menú
    UI opcionLeida;//aquí se guarda la última opción leída en un menú
    
    Menu(){
    }
    //aquí se procesa el evento que espera a que el usuario introduzca una
    //opcion en el menú, y si es válida, entonces ejecuta la opción deseada
    void leerOpcion(){
        validarEntrada("Introduzca una opcion valida\n",opcionLeida,static_cast<UI>(1),cantidadOpciones);
        seleccionarOpcion(opcionLeida);
    }
    //este método define el código que se ejecutará dependiendo
    //de la opción que el usuario seleccione, por lo tanto es
    //abstracto, ya que las opciones disponibles varían para
    //cada menú.
    virtual void seleccionarOpcion(int op)=0;
    //imprime la lsita de opciones disponibles dentro del menú,
    //igualmente varía según el menú, por eso es abstracto
    virtual void mostrarMenu()=0;
    //este método inicializa un ciclo infinito para la ejecución del menú,
    //se detiene cuando el salir es igual true
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
//se reserva memoria para las variables estáticas de la clase
CatalogoProductos Menu::miCatalogo;
std::time_t Menu::t = std::time(0);
std::tm* Menu::fechaActual = std::localtime(&t);
std::string Menu::textoFechaActual;