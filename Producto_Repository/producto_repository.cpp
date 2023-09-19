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
        cout<<"No hay productos registrados"<<endl;
        return;
    }
    gotoxy(12, 10);
    cambiarColor(11);
    cout<<"ID: ";
    gotoxy(20, 10);
    cout<<"Nombre: ";
    gotoxy(35, 10);
    cout<<"Cantidad: ";
    gotoxy(45, 10);
    cout<<"Precio: ";
    gotoxy(55, 10);
    cout<<"Lote: ";
    gotoxy(65, 10);
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
        gotoxy(12, 11+i);
        cout<<productos[i].id;
        gotoxy(20,11+i);
        cout<<productos[i].nombre;
        gotoxy(35, 11+i);
        cout<<productos[i].cantidad;
        gotoxy(45,11+i);
        cout<<productos[i].precio;
        gotoxy(55,11+i);
        cout<<productos[i].lote;
        gotoxy(65,11+i);
        cout<<categoria;
        gotoxy(0,11+i+2);
    }

}
void ProductoRepository::eliminar(int id)
{
    if (!this->existeProducto(id)){
        cout<<"No existe dicho producto\n";
        return;
    }
    Producto p;
    for(int i =0;i<productos.size();i++){
        if(productos[i].id == id){
            p = productos[i];
            productos.erase(productos.begin()+i);
            fileManager.eliminar(p);
            cout<<"Producto eliminado correctamente"<<endl;
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