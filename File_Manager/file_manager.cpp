#include "file_manager.h"
#include "../Producto/Producto.h"
#include <string.h>
#include <iostream>
using namespace std;
bool FileManager::existeArchivo()
{
    archivo = fopen(nombre_archivo,"r");
    if (archivo == nullptr){
        fclose(archivo);
        return true;
    }
    return false;
}

FILE *FileManager::getArchivo()
{
    return archivo;
}
Producto FileManager::obtenerObjeto(int id){
    Producto producto;
    archivo = fopen("productos.dat", "rt");
    if (archivo == NULL) {
        cout << "Error al abrir el archivo\n";
        return producto;
    }
    while(fread(&producto, sizeof(Producto), 1, archivo)){
        if(producto.id == id){
            break;
        }
    }
    fclose(archivo);
    return producto;

}
bool FileManager::finalArchivo()
{
    return feof(archivo);
}

void FileManager::escribir(Producto objeto)
{
    if (existeArchivo()){
        archivo = fopen(this->nombre_archivo,"w");
        fwrite(&objeto,sizeof(objeto),1,archivo);
        fclose(archivo);
    }
    else{
        archivo = fopen(this->nombre_archivo,"a");
        fwrite(&objeto,sizeof(objeto),1,archivo);
        fclose(archivo);
    }
}

void FileManager::modificar(Producto producto)
{
    archivo = fopen("productos.dat", "r+b");
    if (archivo == NULL) {
        cout << "Error al abrir el archivo\n";
        return;
    }
    Producto registro;
    while (fread(&registro, sizeof(Producto), 1, archivo)) {
        if (registro.id == producto.id) {
            // Modificar los campos del registro
            strcpy(registro.nombre, producto.nombre);
            registro.cantidad = producto.cantidad;
            registro.precio = producto.precio;
            strcpy(registro.lote, producto.lote);
            registro.categoria = producto.categoria;
            // Escribir el registro modificado en el archivo
            fseek(archivo, -sizeof(Producto), SEEK_CUR);
            fwrite(&registro, sizeof(Producto), 1, archivo);
            break;
        }
    }
    fclose(archivo);
}

Producto FileManager::leer(Producto producto)
{
    archivo = fopen(nombre_archivo,"rt");
    fread(&producto,sizeof(producto),1,archivo);
    cerrar();
    return producto;
}

void FileManager::cerrar()
{

    fclose(archivo);
}