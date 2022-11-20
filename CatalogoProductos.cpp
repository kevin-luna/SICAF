#pragma once
#include <iostream>
#include <map>
#include <iomanip>
#include <fstream>
#include "Cafeteria.cpp"
#include "Producto.cpp"
class CatalogoProductos{
    public:
    static std::fstream archivoCatalogo;
    static std::map<std::string,Producto> catalogoProductos;
    CatalogoProductos(){}
    ~CatalogoProductos(){}
    CatalogoProductos(std::map<std::string,Producto> &c){
        catalogoProductos=c;
        cargarCatalogo();
    }

    void operator=(const CatalogoProductos &catalogo){
        catalogoProductos = catalogo.catalogoProductos;
    }

    void cargarCatalogo(){
        if(catalogoProductos.empty()){
            archivoCatalogo.open("Catalogo.txt",READ);
            while(archivoCatalogo){
                std::getline(archivoCatalogo,catalogoProductos["tmp"].id,';');
                if(catalogoProductos["tmp"].id.size()==0)break;
                std::getline(archivoCatalogo,catalogoProductos["tmp"].nombre,';');
                archivoCatalogo>>catalogoProductos["tmp"].precio;
                archivoCatalogo.ignore();
                catalogoProductos[catalogoProductos["tmp"].id]=catalogoProductos["tmp"];
                // std::cout<<"|ID:"<<catalogoProductos[catalogoProductos["tmp"].id].id<<"| Nombre:"<<catalogoProductos[catalogoProductos["tmp"].id].nombre<<"| Precio:"<<catalogoProductos[catalogoProductos["tmp"].id].precio<<"|\n";
            }
            catalogoProductos.erase("tmp");
            std::cout<<catalogoProductos.size()<<" productos cargados exitosamente\n";
            // for(auto p:catalogoProductos){
            //     std::cout<<p.second.id<<" "<<p.second.nombre<<" "<<p.second.precio<<"\n";
            // }
            archivoCatalogo.close();
        }
    }

    bool buscarProducto(std::string id){
        return catalogoProductos.count(id)>0?true:false;
    }

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

std::map<std::string,Producto> CatalogoProductos::catalogoProductos;
std::fstream CatalogoProductos::archivoCatalogo;