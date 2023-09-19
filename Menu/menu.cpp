#include"menu.h"
#include<iostream>
#include<conio.h>
#include<string.h>
#include"../Producto/Producto.h"
#include"../Producto_Repository/producto_Repository.h"
#include"../funciones/funciones.h"

using namespace std;
void imprimirMenu(){
    gotoxy(45,2);
    cout<<"\033[1;33mSistema de inventario\033[0m"<<endl<<endl;
    //Fila 1 Columna 1;
    gotoxy(30,4);
    cout<<"[1] Agregar registro";
    //Fila 1 Columna 2
    gotoxy(62, 4);
    cout<<"[2] Modificar registro";
    //Fila 2 Columna 1
    gotoxy(30, 6);
    cout<<"[3] Generar reporte";
    //Fila 2 Columna 2
    gotoxy(62, 6);
    cout<<"[4] Eliminar registro";
    //Fila 3 Columna 1
    gotoxy(30, 8);
    cout<<"[5] \033[5;31mSalir\033[0m";
    //Fila 4 Columna1
    gotoxy(30, 10);
    cout<<">>";
}
void menu_agregarProductos(ProductoRepository& productoRepository){
    system("cls");  
    gotoxy(45, 2);
    cout<<"\033[1;33mNuevo producto\033[0m";
    while (true){
        fflush(stdin);
        Producto producto;
        producto.id = productoRepository.nuevaID();
        gotoxy(30, 4);
        cout<<"Ingrese el nombre del producto: ";cin.getline(producto.nombre,60,'\n');
        gotoxy(30, 6);
        cout<<"Ingrese la cantidad disponible: ";cin>>producto.cantidad;
        gotoxy(30, 8);
        cout<<"Ingrese el precio: ";cin>>producto.precio;
        gotoxy(30, 10);
        cout<<"Ingrese el lote: ";cin>>producto.lote;
        gotoxy(30, 12);
        producto.categoria = seleccionarCategoria();
        productoRepository.agregar(producto);
        gotoxy(30, 24);
        cout<<"Desea agregar otro producto? (presione s/n)";
        if (getch() == 'n'){
            break;
        }
        system("cls");
    }

}
Categoria seleccionarCategoria(){
    int opcion;
    cout<<"Seleccione la categoria del producto: ";
    gotoxy(30, 14);
    cout<<"1. Alimentos";
    gotoxy(30, 16);
    cout<<"2. Bebidas";
    gotoxy(30, 18);
    cout<<"3. Limpieza";
    gotoxy(30, 20);
    cout<<"4. Otros";
    gotoxy(30, 22);
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
void menu_modificarProductos(ProductoRepository& productoRepository){
    system("cls");
    Producto registro;
            fflush(stdin);
            int id;
            int modOpc;
            modOpc = 1;
            cout<<"MODIFICAR REGISTRO -- DIGITE 0 PARA SALIR\n";
            cout<<"Ingrese la id del producto a modificar: ";cin>>id;
            //Si la id es 0, salir
            if(id == 0){
                return;
            }
            registro = productoRepository.obtenerProducto(id);
            if(!productoRepository.existeProducto(registro.id)){
                cout<<"No se ha encontrado el producto"<<endl;
                return;
            };
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
            else{
                cout<<"Opcion invalida\n";
            }
}

void menu_eliminarProducto(ProductoRepository& productoRepository){
    system("cls");
    int id;
    cout<<"Ingrese la id del producto a eliminar: ";cin>>id;
    productoRepository.eliminar(id);
}

void menu_generarReporte(ProductoRepository& productoRepository){
    system("cls");
    gotoxy(45, 2);
    cambiarColor(6);
    cout<<"Reporte de inventario\n\n";
    productoRepository.generarReporte();
}