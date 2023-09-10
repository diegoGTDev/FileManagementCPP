#include "producto_repository.h"
#include "../File_Manager/file_manager.h"
#include<iostream>
#include<string.h>
using namespace std;
void ProductoRepository::agregar(Producto producto)
{
    fileManager.escribir(producto);
}

void ProductoRepository::modificar(Producto producto)
{
    fileManager.modificar(producto);
}
Producto obtenerProducto(int id){

}
void ProductoRepository::generarReporte()
{
    
FILE *archivo;
archivo = fopen("productos.dat", "rt");
if (archivo == NULL) {
    cout << "Error al abrir el archivo\n";
}
Producto producto;
while (fread(&producto, sizeof(Producto), 1, archivo)) {
    // process the record
    //Show al producto properties
    cout<<"ID: "<<producto.id<<endl;
    cout<<"Nombre: "<<producto.nombre<<endl;
    cout<<"Cantidad: "<<producto.cantidad<<endl;
    cout<<"Precio: "<<producto.precio<<endl;
    cout<<"Lote: "<<producto.lote<<endl;
    cout<<"Categoria: "<<producto.categoria<<endl;
    cout<<"-----------------------------------\n";
}
if (feof(archivo)) {
    cout << "Llegaste al final del archivo\n";
} else {
    cout << "Error al leer el archivo\n";
}
fclose(archivo);
}

Producto ProductoRepository::obtenerProducto(int id)
{
    Producto result;
    result = fileManager.obtenerObjeto(id);
    return result;
}
