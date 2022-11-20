#include <iostream>
#include "MenuPrincipal.cpp"
#include "Producto.cpp"
#include "CatalogoProductos.cpp"
int main(){
    std::cout<<"-------------------------------Equipo: DAMEX-SICAF-----------------------------------\n";
    std::cout<<"---------------------Proyecto Final software de una cafeteria------------------------\n";
    std::cout<<"---------------------Bienvenidos al software de la cafeteria-------------------------\n";
    std::cout<<"----A continuacion se te mostrara el menu principal de las funciones del programa----\n";
    MenuPrincipal menuPrincipal;
    menuPrincipal.iniciar();
    std::cout<<"Hasta pronto!!!\n";
}