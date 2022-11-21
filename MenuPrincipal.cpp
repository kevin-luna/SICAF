#pragma once
#include "Menu.cpp"
#include "MenuPedidos.cpp"
#include "MenuProductos.cpp"
#include "Producto.cpp"
#include "CatalogoProductos.cpp"
#include "MenuRegistroVentas.cpp"
class MenuPrincipal:public Menu{
    public:
    // std::map<std::string,Producto> catalogoProductos;
    // static CatalogoProductos miCatalogo;
    MenuPrincipal():Menu(){
        cantidadOpciones=5;
        // miCatalogo=CatalogoProductos(catalogoProductos);
        miCatalogo.cargarCatalogo();
    }
    ~MenuPrincipal(){};
    void mostrarMenu(){
        std::cout<<"Por favor seleccione una opción:\n";
        std::cout<<"[1] Realizar un pedido\n";
        std::cout<<"[2] Registrar un producto\n";
        std::cout<<"[3] Ver Registro de ventas\n";
        std::cout<<"[4] Cerrar registro de ventas de hoy\n";
        std::cout<<"[5] Salir\n";
    }
    void seleccionarOpcion(int op) override{
        // std::cout<<"Opcion seleccionada: "<<op<<"\n";
        if(op==1){
            MenuPedidos menuPedidos;
            menuPedidos.iniciar();
        }else if(op==2){
            MenuProductos menuProductos;
            menuProductos.iniciar();
        }else if(op==3){
            MenuRegistroVentas menuRegistros;
            menuRegistros.iniciar();
        }else if(op==4){

        }else cerrar();
    }
};