#include "producto_repository.h"
#include"../Producto/Producto.h"
#include "../File_Manager/file_manager.h"
#include<iostream>
#include<string.h>
using namespace std;

void ProductoRepository::init()
{
    //Get all the data in the file and save it on the vector
    FILE *archivo;
    archivo = fopen(nombre_archivo, "rt");
    Producto producto;
    while (fread(&producto, sizeof(Producto), 1, archivo)) {
        // process the record
        productos.push_back(producto);
    }
    fclose(archivo);


}
void ProductoRepository::agregar(Producto producto)
{
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
    for(int i = 0; i<productos.size(); i++){
        char categoria[20];
        switch(productos[i].categoria){
            case 0: strcpy(categoria, "Alimentos");break;
            case 1: strcpy(categoria, "Bebidas");break;
            case 2: strcpy(categoria, "Limpieza");break;
            case 3: strcpy(categoria, "Otros");break;
        }
        cout<<"ID: "<<productos[i].id<<endl;
        cout<<"Nombre: "<<productos[i].nombre<<endl;
        cout<<"Cantidad: "<<productos[i].cantidad<<endl;
        cout<<"Precio: "<<productos[i].precio<<endl;
        cout<<"Lote: "<<productos[i].lote<<endl;
        cout<<"Categoria: "<<categoria<<endl;
        cout<<"-----------------------------------\n";
    }

}
void ProductoRepository::eliminar(int id)
{
    Producto p;
    for(int i =0;i<productos.size();i++){
        if(productos[i].id == id){
            p = productos[i];
            productos.erase(productos.begin()+i);
            fileManager.eliminar(p);
        }
    }
    
}

int ProductoRepository::obtenerCantidadProductos()
{
    return productos.size();
}
