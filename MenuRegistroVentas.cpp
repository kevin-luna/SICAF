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
    MenuRegistroVentas(){
        cantidadOpciones=5;
    }
    void mostrarMenu() override{
        std::cout<<"[1] Registro total de ventas.\n";
        std::cout<<"[2] Registro de ventas por mesa.\n";
        std::cout<<"[3] Registro de ventas por producto.\n";
        std::cout<<"[4] Registro de ventas de productos por intervalo.\n";
        std::cout<<"[5] Regresar.\n";
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
            std::cout<<"|    Fecha de la venta:    |    Producto    |    Precio    |    Cantidad    |\n";
            while (std::getline(archivoRegistro,tmp,';') && tmp.size()>0)
            {
                std::cout<<tmp<<"    ";
                std::getline(archivoRegistro,tmp,';');
                std::cout<<CatalogoProductos::catalogoProductos[tmp].nombre<<"    $"<<std::fixed<<std::setprecision(2)<<CatalogoProductos::catalogoProductos[tmp].precio<<"    ";
                std::getline(archivoRegistro,tmp,';');
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
            validarEntrada("Por favor introduzca una mesa válida.\n",opcionLeida,static_cast<UI>(1),static_cast<UI>(5));
            mostrarRegistro("RegistroVentas/Mesa/"+std::to_string(opcionLeida)+".txt");
        }else if(op==3){
            std::cin.ignore(MAX_BUFF_SIZE,'\n');
            std::cout<<"Introduzca el ID del producto:";
            std::getline(std::cin,tmp);
            if(miCatalogo.buscarProducto(tmp))mostrarRegistro("RegistroVentas/Producto/"+tmp+".txt");
            else std::cout<<"No existe el producto con el ID "+tmp<<".\n";
        }else if(op==4){
            std::cout<<"Seleccione un mes (entre 1 y 12): ";
            validarEntrada("Por favor seleccione un mes valido (entre 1 y 12).\n",opcionLeida,static_cast<UI>(1),static_cast<UI>(12));
            std::cout<<"Ingrese el ID del producto:";
            std::cin.ignore(MAX_BUFF_SIZE,'\n');
            std::getline(std::cin,tmp);
            if(miCatalogo.buscarProducto(tmp)){
                if(!std::filesystem::exists("RegistroVentas/Producto/"+tmp+".txt")){
                    std::cout<<"El archivo no existe\n.";
                    return;
                }
                if(std::filesystem::is_empty("RegistroVentas/Producto/"+tmp+".txt")){
                    std::cout<<"El registro esta vacio.\n";
                    return;
                }else{
                    std::vector<float> ventasDelMes(32,0.0);
                    UI dia,mes,elementos=0;
                    float precio=0;
                    archivoRegistro.open("RegistroVentas/Producto/"+tmp+".txt");
                    while(std::getline(archivoRegistro,tmp,'-') && tmp.size()>0){//Lee el dia
                        dia=std::stoi(tmp);
                        std::getline(archivoRegistro,tmp,'-');//Lee el mes
                        mes=std::stoi(tmp);
                        std::getline(archivoRegistro,tmp,';');//Lee el año
                        std::getline(archivoRegistro,tmp,';');//Lee el ID
                        if(mes==opcionLeida){
                            precio=CatalogoProductos::catalogoProductos[tmp].precio;
                            std::getline(archivoRegistro,tmp,';');
                            ventasDelMes[dia]+=precio*std::stoi(tmp);
                            ++elementos;
                        }
                    }
                    archivoRegistro.close();
                    if(elementos==0){
                        std::cout<<"No hubo ventas del producto en el mes seleccionado.\n";
                        return;
                    }
                    SegmentTree arbolDeSegmentos(ventasDelMes);
                    std::cout<<"Leyendo consultas:\n";
                    std::cout<<"Cuando desee terminar, ingrese 0 para ambos limites.\n";
                    int izquierdo=0,derecho=0;
                    while(1){
                        std::cout<<"Ingrese el limite izquierdo del intervalo:";
                        validarEntrada("Por favor ingrese un valor entre 1 y 31.",izquierdo,0,31);
                        std::cout<<"Ingrese el limite derecho del intervalo:";
                        validarEntrada("Por favor ingrese un valor entre 1 y 31.",derecho,0,31);
                        if(izquierdo==0 && derecho==0)break;
                        if(izquierdo>derecho || izquierdo==0 || derecho==0)std::cout<<"Consulta invalida.\n";
                        else{
                            std::cout<<"La venta del producto entre "<<izquierdo<<" y "<<derecho<<" del mes, fue de:";
                            std::cout<<"$"<<std::fixed<<std::setprecision(2)<<arbolDeSegmentos.consultaSuma(izquierdo,derecho)<<"\n";
                        }
                    }
                }
            }else{
                std::cout<<"No hay un producto con ese ID.\n";
            }
        }
        else if(op==5) cerrar();
    }
};