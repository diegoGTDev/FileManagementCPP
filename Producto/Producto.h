#ifndef Producto_H
#define Producto_H
enum Categoria{alimentos, bebidas, limpieza, otros};	
struct Producto{
    int id;
    char nombre[60];
    int cantidad;
    int precio;
    char lote[40];
    Categoria categoria;
};

#endif