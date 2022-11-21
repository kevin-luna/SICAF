#pragma once
#include "Menu.cpp"
#include "Cafeteria.cpp"
#include <iomanip>
class MenuPedidos:public Menu{
    private:
    public:
    std::list<Pedido> pedidosPorMesa[6];
    float totalAcumulado = 0.0;
    UI numeroMesa;
    std::string tmp;
    static float totalVentasDia;
    static std::string nombreArchivoRVentasMesa;
    static std::string nombreArchivoRVentasProd;
    std::string nombreTicket;
    static std::fstream RegistroVentasMesa;
    static std::fstream RegistroVentasProducto;
    std::fstream Ticket;
    MenuPedidos():Menu(){
        cantidadOpciones=5;
        std::cout<<"Ingrese el numero de mesa: ";
        validarEntrada("Por favor seleccione una mesa valida.\n",numeroMesa,static_cast<UI>(1),static_cast<UI>(5));
    }

    void mostrarMenu() override{
        std::cout<<"[1] Agregar productos\n";
        std::cout<<"[2] Modificar la cantidad de un producto\n";
        std::cout<<"[3] Eliminar un producto\n";
        std::cout<<"[4] Finalizar pedido y generar ticket\n";
        std::cout<<"[5] Cancelar pedido\n";
    }

    void mostrarPedidoActual(){
        if(pedidosPorMesa[numeroMesa].empty()){
            std::cout<<"Aun no hay productos dentro del pedido.\n";
        }else{
            std::cout<<"Numero de mesa: Mesa "<<numeroMesa<<"\n";
            std::cout<<"Contenido del pedido:\n";
            std::cout<<"|\tID\t|\tProducto\t|\tPrecio\t|\tCantidad\t|\n";
            for(auto i:pedidosPorMesa[numeroMesa]){
                std::cout<<i.id<<" "<<CatalogoProductos::catalogoProductos[i.id].nombre<<" $"<<std::fixed<<std::setprecision(2)<<CatalogoProductos::catalogoProductos[i.id].precio<<" "<<i.cantidad<<"\n";
            }
        }
        std::cout<<"TOTAL: "<<std::fixed<<std::setprecision(2)<<totalAcumulado<<"\n";
    }

    void seleccionarOpcion(int op) override{
        if(op==1){
            std::cout<<"¿Cuantos productos desea agregar al pedido?\n";
            validarEntrada("Por favor ingrese solo un entero positivo.\n",opcionLeida);
            std::cin.ignore(MAX_BUFF_SIZE,'\n');
            for(UI p=1;p<=opcionLeida;p++){
                std::cout<<"Ingrese el ID del producto:";
                pedidosPorMesa[numeroMesa].push_back({});
                while(1){
                    std::getline(std::cin,pedidosPorMesa[numeroMesa].back().id);
                    if(miCatalogo.buscarProducto(pedidosPorMesa[numeroMesa].back().id))break;
                    std::cout<<"El ID ingresado no existe en el catalogo, intente de nuevo.\n";
                }
                std::cout<<"Ingrese la cantidad del producto:";
                validarEntrada("Por favor, ingrese una cantidad positiva.",pedidosPorMesa[numeroMesa].back().cantidad);
                totalAcumulado+=pedidosPorMesa[numeroMesa].back().cantidad*CatalogoProductos::catalogoProductos[pedidosPorMesa[numeroMesa].back().id].precio;
                std::cout<<"Producto agregado exitosamente!\n";
                std::cin.ignore(MAX_BUFF_SIZE,'\n');
            }
            mostrarPedidoActual();
        }else if(op==2){
            if(pedidosPorMesa[numeroMesa].empty()){
                std::cout<<"Aun no hay productos agregados al pedido\n";
            }else{
                mostrarPedidoActual();
                std::cout<<"Ingrese el ID del producto a modificar:";
                std::cin.ignore(MAX_BUFF_SIZE,'\n');
                std::getline(std::cin,tmp);
                auto itr = pedidosPorMesa[numeroMesa].begin();
                for(;itr!=pedidosPorMesa[numeroMesa].end();itr++){
                    if(itr->id==tmp){
                        totalAcumulado-=itr->cantidad*CatalogoProductos::catalogoProductos[itr->id].precio;
                        std::cout<<"Ingrese la nueva cantidad: ";
                        std::cin.ignore(MAX_BUFF_SIZE,'\n');
                        validarEntrada("Por ingrese un valor positivo.",itr->cantidad);
                        totalAcumulado+=itr->cantidad*CatalogoProductos::catalogoProductos[itr->id].precio;
                        break;
                    }
                }
                if(itr==pedidosPorMesa[numeroMesa].end())
                    std::cout<<"El elemento con el ID introducido no existe.\n";
                else{
                    std::cout<<"La cantidad del producto deseado fue modificada exitosamente.\n";
                    mostrarPedidoActual();
                }
            }
        }else if(op==3){
            if(pedidosPorMesa[numeroMesa].empty())
                std::cout<<"Aun no hay productos agregados al pedido\n";
            else{
                mostrarPedidoActual();
                std::cout<<"Ingrese el ID del producto a eliminar:";
                std::cin.ignore(MAX_BUFF_SIZE,'\n');
                std::getline(std::cin,tmp);
                auto itr = pedidosPorMesa[numeroMesa].begin();
                for(;itr!=pedidosPorMesa[numeroMesa].end();itr++){
                    if(itr->id==tmp){
                        totalAcumulado-=itr->cantidad*CatalogoProductos::catalogoProductos[itr->id].precio;
                        pedidosPorMesa[numeroMesa].erase(itr);
                        break;
                    }
                }
                if(itr==pedidosPorMesa[numeroMesa].end())
                    std::cout<<"El elemento con el ID introducido no existe.\n";
                else{
                    std::cout<<"Producto eliminado exitosamente.\n";
                    mostrarPedidoActual();
                }
            }
        }else if(op==4){
            if(pedidosPorMesa[numeroMesa].empty())
                std::cout<<"Aun no hay productos agregados al pedido\n";
            else{
                mostrarPedidoActual();
                std::cout<<"¿Desea continuar con la impresion del ticket? (S/N):";
                std::cin.ignore(MAX_BUFF_SIZE,'\n');
                std::getline(std::cin,tmp);
                if(tmp=="S" || tmp=="s"||tmp=="Si"||tmp=="si"){
                    nombreTicket="Tickets/"+std::to_string(currentDate->tm_mday)+"-"+std::to_string(currentDate->tm_mon)+"-"+std::to_string(currentDate->tm_year+1900)+"-"+std::to_string(currentDate->tm_hour)+":"+std::to_string(currentDate->tm_min)+".txt";
                    Ticket.open(nombreTicket,WRITE);
                    Ticket<<"---DEV'S COFFEE---\n";
                    Ticket<<"FECHA: "<<currentDate->tm_mday<<"/"<<currentDate->tm_mon<<"/"<<currentDate->tm_year+1900<<"\n";
                    Ticket<<"HORA: "<<currentDate->tm_hour<<":"<<currentDate->tm_min<<"\n";
                    Ticket<<"Numero de mesa: Mesa "<<numeroMesa<<"\n";
                    Ticket<<"Contenido del pedido:\n";
                    Ticket<<"|\tID\t|\tProducto\t|\tPrecio\t|\tCantidad\t|\n";
                    for(auto i:pedidosPorMesa[numeroMesa]){
                        Ticket<<i.id<<" "<<CatalogoProductos::catalogoProductos[i.id].nombre<<" $"<<std::fixed<<std::setprecision(2)<<CatalogoProductos::catalogoProductos[i.id].precio<<" "<<i.cantidad<<"\n";
                    }
                    Ticket<<"TOTAL: "<<std::fixed<<std::setprecision(2)<<totalAcumulado<<"\n";
                    Ticket<<"¡GRACIAS POR SU COMPRA!";
                    Ticket.close();
                    cerrar();
                }
            }
        }
        else if(op==5)cerrar();

    }
};

float MenuPedidos::totalVentasDia=0.0;