#include <iostream>
#include <filesystem>
#include "Menu.cpp"
#include "Cafeteria.cpp"
#include "SegmentTree.cpp"
class MenuRegistroVentas:public Menu{
    private:
    std::fstream archivoRegistro;
    public:
    std::string tmp;
    int auxiliar;
    MenuRegistroVentas(){
        cantidadOpciones=4;
    }
    void mostrarMenu() override{
        std::cout<<"[1] Registro total de ventas.\n";
        std::cout<<"[2] Registro de ventas por mesa.\n";
        std::cout<<"[3] Registro de ventas por producto.\n";
        std::cout<<"[4] Regresar.\n";
    }
    void mostrarRegistro(std::string registro){
        if(!std::filesystem::exists(registro)){
            std::cout<<"El registro aun no ha sido creado.\n";
            return;
        }
        archivoRegistro.open(registro,READ);
        if(std::filesystem::is_empty(registro)){
            std::cout<<"El registro esta vacio.\n";
        }else{
            std::cout<<"|    Fecha de la venta:    |    ID del prod.    |    Nombre del prod.    |    Precio del prod.    |\n";
            while (std::getline(archivoRegistro,tmp) && tmp.size()>0)
            {
                std::cout<<tmp<<"\n";
            }
            archivoRegistro.close();
        }
    }
    void seleccionarOpcion(int op){
        if(op==1){
            mostrarRegistro("RegistroVentas/VentasTotales.txt");
        }else if(op==2){
            std::cout<<"Introduzca el numero de la mesa.\n";
            validarEntrada("Por favor introduzca una mesa válida.\n",auxiliar,1,5);
            mostrarRegistro("RegistroVentas/Mesa/"+std::to_string(auxiliar)+".txt");
        }else if(op==3){
            std::cin.ignore(MAX_BUFF_SIZE,'\n');
            std::cout<<"Introduzca el ID del producto:";
            std::getline(std::cin,tmp);
            if(miCatalogo.buscarProducto(tmp))mostrarRegistro("RegistroVentas/Producto/"+tmp+".txt");
            else std::cout<<"No existe el producto con el ID "+tmp<<".\n";
        }else if(op==4) cerrar();
    }
};