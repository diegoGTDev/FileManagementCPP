#include<iostream>
#include <conio.h>
#include "Producto/Producto.h"
#include "Producto_Repository/producto_Repository.h"
#include "Menu/menu.h"
#include "funciones/funciones.h"
using namespace std;

int main(){
    system("Title Sistema de inventario");
    ProductoRepository productoRepository("inventario");
    bool esperarTecla = true;
    inicio:
    system("cls");
    imprimirMenu();
    switch(getch()){
        case '1': 
            esperarTecla = menu_agregarProductos(productoRepository);break;
        case '2': 
            menu_modificarProductos(productoRepository);
            break;
        case '3': menu_generarReporte(productoRepository);break;
        case '4': 
            menu_eliminarProducto(productoRepository);
            break;
        case '5': 
            system("cls");
            gotoxy(45, 10);
            cout<<"\033[1;31mHas salido correctamente\033[0m\n\n\n\n";
            return 0;
            break;
    }
    if (esperarTecla){
        getch();
    }
    else{
        esperarTecla = true;
    }
    goto inicio;
    return 0;
}
