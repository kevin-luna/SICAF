#pragma once
#include <map>
#include <vector>
#include "Menu.cpp"
#include "Producto.cpp"
#include "Cafeteria.cpp"
#include "CatalogoProductos.cpp"
class MenuProductos:public Menu{
    public:
    MenuProductos():Menu(){
        cantidadOpciones=2;
    }
    void mostrarMenu() override{
        std::cout<<"[1] Agregar productos nuevos\n";
        std::cout<<"[2] Cancelar\n";
    }
    void seleccionarOpcion(int op) override{
        if(op==1){
            std::cout<<"¿Cuántos productos desea agregar?: ";
            validarEntrada("Por favor ingrese un entero positivo.",opcionLeida);
            //llama al método agregar productos del controlador del catálogo
            miCatalogo.agregarProductos(opcionLeida);
        }else if(op==2)cerrar();
    }
};