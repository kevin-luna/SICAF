#include <iostream>
#include <filesystem>
#include "Menu.cpp"
#include "Cafeteria.cpp"
#include "SegmentTree.cpp"
class MenuRegistroVentas:public Menu{
    private:
    std::fstream archivoRegistro;
    public:
    std::string tmp;//buffer para procesar la entrada
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
        //verifica que exista el archivo de registro antes de imprimir
        if(!std::filesystem::exists(registro)){
            std::cout<<"El registro aun no ha sido creado.\n";
            return;
        }
        archivoRegistro.open(registro,READ);
        //verifica que el archivo no esté vacío
        if(std::filesystem::is_empty(registro)){
            std::cout<<"El registro esta vacio.\n";
        }else{
            //imprime los registros
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
            //imprime el registro de ventas totales
            mostrarRegistro("RegistroVentas/VentasTotales.txt");
        }else if(op==2){//proceso para imprimir registro de ventas por mesa
            std::cout<<"Introduzca el numero de la mesa.\n";
            validarEntrada("Por favor introduzca una mesa válida.\n",opcionLeida,static_cast<UI>(1),static_cast<UI>(5));
            //imprime el registro de ventas de la mesa especificada
            mostrarRegistro("RegistroVentas/Mesa/"+std::to_string(opcionLeida)+".txt");
        }else if(op==3){//proceso para imprimir registro de ventas por producto
            std::cin.ignore(MAX_BUFF_SIZE,'\n');
            std::cout<<"Introduzca el ID del producto:";
            std::getline(std::cin,tmp);
            //comprueba si existe un producto con el ID proporcionado
            //y si existe imprime su registro de ventas
            if(miCatalogo.buscarProducto(tmp))mostrarRegistro("RegistroVentas/Producto/"+tmp+".txt");
            else std::cout<<"No existe el producto con el ID "+tmp<<".\n";
        }else if(op==4){//proceso para imprimir registro de ventas por producto en un intervalo de tiempo
            std::cout<<"Seleccione un mes (entre 1 y 12): ";
            validarEntrada("Por favor seleccione un mes valido (entre 1 y 12).\n",opcionLeida,static_cast<UI>(1),static_cast<UI>(12));
            std::cout<<"Ingrese el ID del producto:";
            std::cin.ignore(MAX_BUFF_SIZE,'\n');
            std::getline(std::cin,tmp);
            //comprueba que el producto se encuentre en el catálogo
            if(miCatalogo.buscarProducto(tmp)){
                //comprueba que el archivo de registro exista
                if(!std::filesystem::exists("RegistroVentas/Producto/"+tmp+".txt")){
                    std::cout<<"El archivo no existe\n.";
                    return;
                }
                //comprueba que el archivo contenga registros
                if(std::filesystem::is_empty("RegistroVentas/Producto/"+tmp+".txt")){
                    std::cout<<"El registro esta vacio.\n";
                    return;
                }else{
                    //inicializa un vector que contenga las ventas de ese producto dentro del mes
                    std::vector<float> ventasDelMes(32,0.0);
                    UI dia,mes,elementos=0;
                    float precio=0;
                    archivoRegistro.open("RegistroVentas/Producto/"+tmp+".txt");
                    //se leen los registros
                    while(std::getline(archivoRegistro,tmp,'-') && tmp.size()>0){//Lee el dia
                        dia=std::stoi(tmp);
                        std::getline(archivoRegistro,tmp,'-');//Lee el mes
                        mes=std::stoi(tmp);
                        std::getline(archivoRegistro,tmp,';');//Lee el año
                        std::getline(archivoRegistro,tmp,';');//Lee el ID
                        //si el registro actual se encuentra dentro del mes seleccionado,
                        //se agrega a la lista el total de la venta
                        if(mes==opcionLeida){
                            precio=CatalogoProductos::catalogoProductos[tmp].precio;
                            std::getline(archivoRegistro,tmp,';');
                            ventasDelMes[dia]+=precio*std::stoi(tmp);
                            ++elementos;//cuenta las ventas dentro del mes
                        }
                    }
                    archivoRegistro.close();
                    if(elementos==0){//si no hubo ventas en el mes, retorna
                        std::cout<<"No hubo ventas del producto en el mes seleccionado.\n";
                        return;
                    }
                    SegmentTree arbolDeSegmentos(ventasDelMes);
                    std::cout<<"Leyendo consultas:\n";
                    std::cout<<"Cuando desee terminar, ingrese 0 para ambos limites.\n";
                    int izquierdo=0,derecho=0;
                    //procesa las consultas
                    while(1){
                        std::cout<<"Ingrese el limite izquierdo del intervalo:";
                        validarEntrada("Por favor ingrese un valor entre 1 y 31.",izquierdo,0,31);
                        std::cout<<"Ingrese el limite derecho del intervalo:";
                        validarEntrada("Por favor ingrese un valor entre 1 y 31.",derecho,0,31);
                        //verifica que los intervalos sean validos
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