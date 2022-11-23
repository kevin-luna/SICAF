#pragma once
#include "Menu.cpp"
#include "MenuPedidos.cpp"
#include "MenuProductos.cpp"
#include "Producto.cpp"
#include "CatalogoProductos.cpp"
#include "MenuRegistroVentas.cpp"
class MenuPrincipal:public Menu{
    public:
    MenuPrincipal():Menu(){
        cantidadOpciones=4;
        miCatalogo.cargarCatalogo();
        //cada que se inicia el menú principal, se carga la fecha actual.
        textoFechaActual=std::to_string(fechaActual->tm_mday)+"-"+std::to_string(fechaActual->tm_mon+1)+"-"+std::to_string(fechaActual->tm_year+1900);
    }
    ~MenuPrincipal(){};
    void mostrarMenu(){
        std::cout<<"Por favor seleccione una opción:\n";
        std::cout<<"[1] Realizar un pedido\n";
        std::cout<<"[2] Registrar un producto\n";
        std::cout<<"[3] Ver Registro de ventas\n";
        std::cout<<"[4] Salir\n";
    }
    void seleccionarOpcion(int op) override{
        if(op==1){
            MenuPedidos menuPedidos;
            menuPedidos.iniciar();
        }else if(op==2){
            MenuProductos menuProductos;
            menuProductos.iniciar();
        }else if(op==3){
            MenuRegistroVentas menuRegistros;
            menuRegistros.iniciar();
        }else if(op==4)
            cerrar();
    }
};