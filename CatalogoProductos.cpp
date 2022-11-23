#pragma once
#include <iostream>
#include <map>
#include <iomanip>
#include <fstream>
#include "Cafeteria.cpp"
#include "Producto.cpp"
//esta clase es un controlador que maneja el catalogo de productos
class CatalogoProductos{
    public:
    //objetos estáticos
    //aquí se cargará el archivo que contiene el registro de productosf
    static std::fstream archivoCatalogo;
    //este map implementa un arbol de busqueda binaria, por lo que nos es útil para
    //realizar méltiples inserciones y múltiples búsquedas de manera rápida
    static std::map<std::string,Producto> catalogoProductos;
    CatalogoProductos(){}
    ~CatalogoProductos(){}

    void cargarCatalogo(){
        //si el map aún no tiene cargado el catálgo, entonces abre el archivo y lee cada registro
        //a su vez que lo lee, inserta cada dato del producto en un nodo dummy en el map,
        if(catalogoProductos.empty()){
            archivoCatalogo.open("Catalogo.txt",READ);
            while(archivoCatalogo){
                std::getline(archivoCatalogo,catalogoProductos["tmp"].id,';');
                if(catalogoProductos["tmp"].id.size()==0)break;
                std::getline(archivoCatalogo,catalogoProductos["tmp"].nombre,';');
                archivoCatalogo>>catalogoProductos["tmp"].precio;
                archivoCatalogo.ignore();
                //una vez que ha rellenado toda la informacion, lo inserta en el nodo adecuado
                catalogoProductos[catalogoProductos["tmp"].id]=catalogoProductos["tmp"];
            }
            //cuando ha terminado de leer los registros elimina el nodo dummy
            catalogoProductos.erase("tmp");
            //finalmente cierra el flujo del archivo
            archivoCatalogo.close();
        }
    }

    //comprueba si un producto ya existe pregutando cuantos
    //elementos existen en el map con esa llave
    bool buscarProducto(std::string id){
        return catalogoProductos.count(id)>0?true:false;
    }

    //este método lee desde la entrada los atributos de un producto
    //y comprueba si ya existe uno dentro del catalogo con el ID
    //proporcionado, si no existe entonces lo carga en el map
    //y lo escribe en el archivo de registro de productos
    void agregarProductos(int cantidad){
        archivoCatalogo.open("Catalogo.txt",APPEND);
        for(int i=1;i<=cantidad;i++){
            catalogoProductos["tmp"].leerProducto();
            std::cout<<"Buscando productos con el ID "<<catalogoProductos["tmp"].id<<"...\n";
            if(buscarProducto(catalogoProductos["tmp"].id)){
                std::cout<<"No ha sido posible agregar el producto.\nYa existe un producto con el identificador proporcionado.\n";
            }else{
                std::cout<<"El producto ha sido registrado con exito\n";
                catalogoProductos[catalogoProductos["tmp"].id]=catalogoProductos["tmp"];
                catalogoProductos["tmp"].guardarProducto(archivoCatalogo);
            }
        }
        catalogoProductos.erase("tmp");
        archivoCatalogo.close();
    }

};
//se reserva memoria para el map y para el flujo del archivo de registro de productos
std::map<std::string,Producto> CatalogoProductos::catalogoProductos;
std::fstream CatalogoProductos::archivoCatalogo;