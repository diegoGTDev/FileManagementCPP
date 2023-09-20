#include "producto_repository.h"
#include"../Producto/Producto.h"
#include "../File_Manager/file_manager.h"
#include<iostream>
#include<string.h>
#include"../funciones/funciones.h"
#include<typeinfo>
using namespace std;

void ProductoRepository::init()
{
    //Cargamos todos los objetos que contenga filemanager en nuestro vector
    //Esto para un manejo sencillo de los datos dentro del codigo
    this->productos = fileManager.leerTodo();
    //Configuración del repositorio
    if (fileConfigManager.existeArchivo() == false){
        /* En caso de no existir  el archivo cfg, crea uno nuevo
            escribiendo en el, el id inicial que será 1.  
        */
        fileConfigManager.escribir(1);
        fileConfigManager.cerrar();
    }
    else{
        int id;
        id = fileConfigManager.leer();
        fileConfigManager.cerrar();
    }


}

void ProductoRepository::agregar(Producto producto)
{
    int newID = producto.id+1;
    fileConfigManager.modificarCFG(newID);
    fileManager.escribir(producto);
    productos.push_back(producto);
}

void ProductoRepository::modificar(Producto producto)
{
    for(int i =0;i<productos.size();i++){
        if(productos[i].id == producto.id){
            productos[i] = producto;
            strcpy(productos[i].nombre, producto.nombre);
            productos[i].cantidad = producto.cantidad;
            productos[i].precio = producto.precio;
            strcpy(productos[i].lote, producto.lote);
            productos[i].categoria = producto.categoria;
            fileManager.modificarP(productos[i]);
        }
    }
}

Producto ProductoRepository::obtenerProducto(int id){
    for(int i =0;i<productos.size();i++){
        if(productos[i].id == id){
            return productos[i];
        }
    }

}
void ProductoRepository::generarReporte()
{
    if (productos.size() == 0){
        gotoxy(42, 5);
        cout<<"\033[1;31mNo hay productos registrados\033[0m"<<endl;
        return;
    }
    cambiarColor(11);
    gotoxy(22, 5);
    cout<<"ID: ";
    gotoxy(30, 5);
    cout<<"Nombre: ";
    gotoxy(45, 5);
    cout<<"Cantidad: ";
    gotoxy(55, 5);
    cout<<"Precio: ";
    gotoxy(65, 5);
    cout<<"Lote: ";
    gotoxy(75, 5);
    cout<<"Categoria: ";
    cambiarColor(15);
    
    for(int i = 0; i<productos.size(); i++){
        char categoria[20];
        switch(productos[i].categoria){
            case 0: strcpy(categoria, "Alimentos");break;
            case 1: strcpy(categoria, "Bebidas");break;
            case 2: strcpy(categoria, "Limpieza");break;
            case 3: strcpy(categoria, "Otros");break;
        }
        gotoxy(22, 6+i);
        cout<<productos[i].id;
        gotoxy(30,6+i);
        cout<<productos[i].nombre;
        gotoxy(45, 6+i);
        cout<<productos[i].cantidad;
        gotoxy(55,6+i);
        cout<<productos[i].precio;
        gotoxy(65,6+i);
        cout<<productos[i].lote;
        gotoxy(75,6+i);
        cout<<categoria;
        gotoxy(0,6+i+2);
    }

}
bool ProductoRepository::eliminar(int id)
{
    if (!this->existeProducto(id)){
        return false;
    }
    Producto p;
    for(int i =0;i<productos.size();i++){
        if(productos[i].id == id){
            p = productos[i];
            productos.erase(productos.begin()+i);
            fileManager.eliminar(p);
            return true;
        }
    }
    
}

int ProductoRepository::nuevaID()
{
    int newID;
    newID = fileConfigManager.leer();
    return newID;
}

bool ProductoRepository::existeProducto(int id){
    for(int i=0; i<productos.size();i++){
        if(productos[i].id == id){
            return true;
        }
    }
    return false;
}