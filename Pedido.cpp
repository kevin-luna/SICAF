#pragma once
#include "Producto.cpp"
class Pedido{
    public:
    std::string id;
    int cantidad;
    void leerPedido();
    void modificarCantidad();
    void guardarPedido();
};