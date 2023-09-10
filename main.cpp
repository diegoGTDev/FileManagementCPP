#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <string>
#include <cstdio>
#include <cstring>
#include "Producto/Producto.h"
#include "Producto_Repository/producto_Repository.h"
using namespace std;
void imprimirMenu();
Categoria seleccionarCategoria();
void menu_agregarProductos(ProductoRepository productoRepository);
int main(){
    ProductoRepository productoRepository("productos.dat");
    inicio:
    fflush(stdin);
    system("cls");
    imprimirMenu();
    switch(getch()){
        case '1': system("cls"); menu_agregarProductos(productoRepository);break;
        case '2': 
            Producto registro;
             fflush(stdin);
            int id;
            int modOpc;
            modOpc = 1;
            cout<<"MODIFICAR REGISTRO -- DIGITE 0 PARA SALIR\n";
            cout<<"Ingrese la id del producto a modificar: ";cin>>id;
            registro = productoRepository.obtenerProducto(id);
            cout<<"Modificar: \n"
            "1. Nombre\n"
            "2. Cantidad\n"
            "3. Precio\n"
            "4. Lote\n"
            "5. Categoria\n";
            cout<<">> ";cin>>modOpc;
            fflush(stdin);
            if (modOpc == 1){
                char new_name[40];
                cout<<"Nuevo nombre: ";
                cin.getline(new_name, 40);
                strcpy(registro.nombre, new_name);
                productoRepository.modificar(registro);
            }
            else if (modOpc == 2){
                int new_cantidad;
                cout<<"Nueva cantidad: ";cin>>new_cantidad;
                registro.cantidad = new_cantidad;
                productoRepository.modificar(registro);
            }
            else if (modOpc == 3){
                //Modificar  el precio
                float new_precio;
                cout<<"Nuevo precio: ";cin>>new_precio;
                registro.precio = new_precio;
                productoRepository.modificar(registro);

            }
            else if (modOpc == 4){
                //Modificar lote
                char new_lote[40];
                cout<<"Nuevo lote: ";
                cin.getline(new_lote, 40);
                strcpy(registro.lote, new_lote);
                productoRepository.modificar(registro);

            }
            else if (modOpc == 5){
                //Modificar categoria
                registro.categoria = seleccionarCategoria();
                productoRepository.modificar(registro);
            }
            else if (modOpc == 0){
                break;
            }
            else{
                cout<<"Opcion invalida\n";
            }
            break;
        case '3': productoRepository.mostrarTodos();break;
        case '4': break;
        case '5': cout<<"Has salido correctamente";return 0;break;
    }
    system("pause");
    goto inicio;
    return 0;
}
Categoria seleccionarCategoria(){
    int opcion;
    cout<<"Seleccione la categoria del producto: \n";
    cout<<"1. Alimentos\n";
    cout<<"2. Bebidas\n";
    cout<<"3. Limpieza\n";
    cout<<"4. Otros\n";
    cout<<"Opcion: ";cin>>opcion;
    switch (opcion){
        case 1:
            return alimentos;
        case 2:
            return bebidas;
        case 3:
            return limpieza;
        case 4:
            return otros;
        default:
            cout<<"Opcion invalida\n";
            return seleccionarCategoria();
    }
}
void imprimirMenu(){
    cout<<"\tSistema de inventario"<<endl<<endl;
    cout<<"[1] Agregar registro\n"
    "[2] Modificar registro\n"
    "[3] Generar reporte\n"
    "[4] Eliminar registro\n"
    "[5] Salir\n";
    cout<<"Presione una opcion\n";
}
void menu_agregarProductos(ProductoRepository productoRepository){
    static int counter = 1;
    while (true){
        fflush(stdin);
        Producto producto;
        producto.id = counter;
        cout<<"Ingrese el nombre del producto: ";cin.getline(producto.nombre,60,'\n');
        cout<<"Ingrese la cantidad disponible: ";cin>>producto.cantidad;
        cout<<"Ingrese el precio: ";cin>>producto.precio;
        cout<<"Ingrese el lote: ";cin>>producto.lote;
        producto.categoria = seleccionarCategoria();
        productoRepository.agregar(producto);
        cout<<"\nDesea agregar otro producto? (s/n): \n";
        if (getch() == 'n'){
            break;
        }
        system("cls");
        counter++;
    }
}