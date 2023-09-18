#include<iostream>
#include <conio.h>
#include "Producto/Producto.h"
#include "Producto_Repository/producto_Repository.h"
#include "Menu/menu.h"
using namespace std;

int main(){
    ProductoRepository productoRepository("productos.dat");
    inicio:
    system("cls");
    imprimirMenu();
    switch(getch()){
        case '1': menu_agregarProductos(productoRepository);break;
        case '2': 
            menu_modificarProductos(productoRepository);
            break;
        case '3': productoRepository.generarReporte();break;
        case '4': 
            menu_eliminarProducto(productoRepository);
            break;
        case '5': cout<<"Has salido correctamente";return 0;break;
    }
    system("pause");
    goto inicio;
    return 0;
}
