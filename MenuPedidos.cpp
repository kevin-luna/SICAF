#pragma once
#include "Menu.cpp"
#include "Cafeteria.cpp"
#include <iomanip>
class MenuPedidos:public Menu{
    private:
    public:
    //lista de adyacencia para almacenar los pedidos por cada mesa
    std::list<Pedido> pedidosPorMesa[6];
    float totalAcumulado = 0.0;//acumulador para calcular el total del pedido
    UI numeroMesa;
    std::string tmp;//buffer para procesar la entrada
    std::string nombreTicket;
    //streams para escribir en los registros
    std::fstream RegistroVentasTotales;
    std::fstream RegistroVentasMesa;
    std::fstream RegistroVentasProducto;
    std::fstream Ticket;
    MenuPedidos():Menu(){
        cantidadOpciones=5;
        //para poder realizar un pedido es necesario indicar el numero de mesa
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
    //imprime los datos de los productos en la lista del pedido
    void mostrarPedidoActual(){
        if(pedidosPorMesa[numeroMesa].empty()){
            std::cout<<"Aun no hay productos dentro del pedido.\n";
        }else{
            std::cout<<"Numero de mesa: Mesa "<<numeroMesa<<"\n";
            std::cout<<"Contenido del pedido:\n";
            std::cout<<"|    ID    |    Producto    |    Precio    |    Cantidad    |\n";
            for(auto i:pedidosPorMesa[numeroMesa]){
                std::cout<<i.id<<" "<<CatalogoProductos::catalogoProductos[i.id].nombre<<" $"<<std::fixed<<std::setprecision(2)<<CatalogoProductos::catalogoProductos[i.id].precio<<" "<<i.cantidad<<"\n";
            }
        }
        std::cout<<"TOTAL: $"<<std::fixed<<std::setprecision(2)<<totalAcumulado<<"\n";
    }

    void seleccionarOpcion(int op) override{
        if(op==1){//proceso para agregar un producto al pedido
            std::cout<<"¿Cuantos productos desea agregar al pedido?\n";
            validarEntrada("Por favor ingrese solo un entero positivo.\n",opcionLeida);
            std::cin.ignore(MAX_BUFF_SIZE,'\n');
            for(UI p=1;p<=opcionLeida;p++){
                std::cout<<"Ingrese el ID del producto:";
                pedidosPorMesa[numeroMesa].push_back({});
                while(1){
                    std::getline(std::cin,pedidosPorMesa[numeroMesa].back().id);
                    //verifica que se ingrese un ID de producto válido
                    if(miCatalogo.buscarProducto(pedidosPorMesa[numeroMesa].back().id))break;
                    std::cout<<"El ID ingresado no existe en el catalogo, intente de nuevo.\n";
                }
                std::cout<<"Ingrese la cantidad del producto:";
                validarEntrada("Por favor, ingrese una cantidad positiva.",pedidosPorMesa[numeroMesa].back().cantidad);
                //suma al total de la compra el costo del producto multiplicado por la cantidad
                totalAcumulado+=pedidosPorMesa[numeroMesa].back().cantidad*CatalogoProductos::catalogoProductos[pedidosPorMesa[numeroMesa].back().id].precio;
                std::cout<<"Producto agregado exitosamente!\n";
                std::cin.ignore(MAX_BUFF_SIZE,'\n');
            }
            mostrarPedidoActual();
        }else if(op==2){//proceso para modificar la cantidad de un producto dentro del pedido
            if(pedidosPorMesa[numeroMesa].empty()){//verifica que el pedido no esté vacío
                std::cout<<"Aun no hay productos agregados al pedido\n";
            }else{
                mostrarPedidoActual();
                std::cout<<"Ingrese el ID del producto a modificar:";
                std::cin.ignore(MAX_BUFF_SIZE,'\n');
                std::getline(std::cin,tmp);
                auto itr = pedidosPorMesa[numeroMesa].begin();
                //itera dentro de la lista del pedido buscando el producto con el ID solicitado
                for(;itr!=pedidosPorMesa[numeroMesa].end();itr++){
                    //si encuentra el elemento, modifica su cantidad
                    if(itr->id==tmp){
                        //resta al total el precio por la cantidad anterior
                        totalAcumulado-=itr->cantidad*CatalogoProductos::catalogoProductos[itr->id].precio;
                        std::cout<<"Ingrese la nueva cantidad: ";
                        validarEntrada("Por ingrese un valor positivo.",itr->cantidad);
                        //suma al total el precio del producto por la nueva cantidad
                        totalAcumulado+=itr->cantidad*CatalogoProductos::catalogoProductos[itr->id].precio;
                        break;
                    }
                }
                //si se llegó al final de la lista significa que el producto
                //no se encuentra en el pedido
                if(itr==pedidosPorMesa[numeroMesa].end())
                    std::cout<<"El elemento con el ID introducido no existe.\n";
                else{
                    std::cout<<"La cantidad del producto deseado fue modificada exitosamente.\n";
                    mostrarPedidoActual();
                }
            }
        }else if(op==3){//proceso para eliminar un producto dentro del pedido
            if(pedidosPorMesa[numeroMesa].empty())
                std::cout<<"Aun no hay productos agregados al pedido\n";
            else{
                mostrarPedidoActual();
                std::cout<<"Ingrese el ID del producto a eliminar:";
                std::cin.ignore(MAX_BUFF_SIZE,'\n');
                std::getline(std::cin,tmp);
                auto itr = pedidosPorMesa[numeroMesa].begin();
                //se itera dentro de la lista buscando el producto con el id solicitado
                for(;itr!=pedidosPorMesa[numeroMesa].end();itr++){
                    //si lo encuentra, lo elimina.
                    if(itr->id==tmp){
                        totalAcumulado-=itr->cantidad*CatalogoProductos::catalogoProductos[itr->id].precio;
                        pedidosPorMesa[numeroMesa].erase(itr);
                        break;
                    }
                }
                //si se llegó al final de la lista significa que el producto
                //no se encuentra en el pedido
                if(itr==pedidosPorMesa[numeroMesa].end())
                    std::cout<<"El elemento con el ID introducido no existe.\n";
                else{
                    std::cout<<"Producto eliminado exitosamente.\n";
                    mostrarPedidoActual();//muestra el estado del pedido después de la eliminación
                }
            }
        }else if(op==4){//proceso para guardar la información del pedido y el total de la compra
            if(pedidosPorMesa[numeroMesa].empty())//verifica que el pedido no esté vacío
                std::cout<<"Aun no hay productos agregados al pedido\n";
            else{
                mostrarPedidoActual();
                std::cout<<"¿Desea continuar con la impresion del ticket? (S/N):";
                std::cin.ignore(MAX_BUFF_SIZE,'\n');
                std::getline(std::cin,tmp);
                if(tmp=="S" || tmp=="s"||tmp=="Si"||tmp=="si"){
                    t = std::time(0);
                    fechaActual = std::localtime(&t);
                    //crea el nombre del archivo del ticket con la fecha y la hora actuales
                    nombreTicket="Tickets/"+std::to_string(fechaActual->tm_mday)+"-"+std::to_string(fechaActual->tm_mon)+"-"+std::to_string(fechaActual->tm_year+1900)+"-"+std::to_string(fechaActual->tm_hour)+"-"+std::to_string(fechaActual->tm_min)+".txt";
                    //se abren los archivos del ticket, el registro de ventas totales y el registro de ventas por mesa
                    Ticket.open(nombreTicket,WRITE);
                    RegistroVentasTotales.open("RegistroVentas/VentasTotales.txt",APPEND);
                    RegistroVentasMesa.open("RegistroVentas/Mesa/"+std::to_string(numeroMesa)+".txt",APPEND);
                    //envía el texto del ticket al archivo
                    Ticket<<"---DEV'S COFFEE---\n";
                    Ticket<<"FECHA: "<<textoFechaActual<<"\n";
                    Ticket<<"HORA: "<<fechaActual->tm_hour<<":"<<fechaActual->tm_min<<"\n";
                    Ticket<<"Numero de mesa: Mesa "<<numeroMesa<<"\n";
                    Ticket<<"Contenido del pedido:\n";
                    Ticket<<"|    ID    |    Producto    |    Precio    |    Cantidad    |\n";
                    for(auto i:pedidosPorMesa[numeroMesa]){
                        Ticket<<i.id<<" "<<CatalogoProductos::catalogoProductos[i.id].nombre<<" $"<<std::fixed<<std::setprecision(2)<<CatalogoProductos::catalogoProductos[i.id].precio<<" "<<i.cantidad<<"\n";
                        RegistroVentasTotales<<textoFechaActual<<";"<<i.id<<";"<<i.cantidad<<";";
                        RegistroVentasMesa<<textoFechaActual<<";"<<i.id<<";"<<i.cantidad<<";";
                        //para cada producto registra su venta en su respectivo registro de venta del producto
                        RegistroVentasProducto.open("RegistroVentas/Producto/"+i.id+".txt",APPEND);
                        RegistroVentasProducto<<textoFechaActual<<";"<<i.id<<";"<<i.cantidad<<";";
                        RegistroVentasProducto.close();
                    }
                    Ticket<<"TOTAL: $"<<std::fixed<<std::setprecision(2)<<totalAcumulado<<"\n";
                    Ticket<<"¡GRACIAS POR SU COMPRA!";
                    //cierra los flujos de los archivos
                    Ticket.close();
                    RegistroVentasTotales.close();
                    RegistroVentasMesa.close();
                    //limpia la lista del pedido de la mesa seleccionada
                    pedidosPorMesa[numeroMesa].clear();
                    totalAcumulado=0.0;//reestablece el total acumulado a 0.0
                    std::cout<<"Ticket generado exitosamente\n";
                    cerrar();
                }
            }
        }
        else if(op==5)cerrar();

    }
};