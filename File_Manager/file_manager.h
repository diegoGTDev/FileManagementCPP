#include<stdio.h>
#include<fstream>
#include <string.h>
#include <iostream>
using namespace std;
#include"../Producto/Producto.h"

#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

template<class T> class FileManager{
    private:
        char* nombre_archivo;
        FILE *archivo;
    public:
        FileManager(char* nombre_archivo){
            this->nombre_archivo = nombre_archivo;
        };

        void escribir(T objeto);
        void eliminar(T objeto);
        void modificar(T producto);
        T leer(T producto);
        T obtenerObjeto(int id);
        bool existeArchivo();
        FILE* getArchivo();
        bool finalArchivo();
        void cerrar();
};

template <typename T>
bool FileManager<T>::existeArchivo()
{
    archivo = fopen(nombre_archivo,"r+b");
    if (archivo == nullptr){
        fclose(archivo);
        return true;
    }
    return false;
}
template <typename T>
FILE *FileManager<T>::getArchivo()
{
    return archivo;
}
template<typename T>
bool FileManager<T>::finalArchivo()
{
    return feof(archivo);
}
template<typename T>
void FileManager<T>::escribir(T objeto)
{
    if (existeArchivo()){
        archivo = fopen(this->nombre_archivo,"w+b");
        fwrite(&objeto,sizeof(objeto),1,archivo);
        fclose(archivo);
    }
    else{
        archivo = fopen(this->nombre_archivo,"a+b");
        fwrite(&objeto,sizeof(objeto),1,archivo);
        fclose(archivo);
    }
}
template<typename T>
void FileManager<T>::modificar(T producto)
{
    archivo = fopen("productos.dat", "r+b");
    // FILE *ftemp = fopen("temp.dat", "w+b");
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
        //fwrite(&registro, sizeof(Producto), 1, ftemp);
    }
    //remove(nombre_archivo);
    // rename("temp.dat", nombre_archivo);
    // fclose(ftemp);
    fclose(archivo);
}
template<typename T>
T FileManager<T>::leer(T producto)
{
    archivo = fopen(nombre_archivo,"r+b");
    fread(&producto,sizeof(producto),1,archivo);
    cerrar();
    return producto;
}
template<typename T>
void FileManager<T>::eliminar(T objeto){
    archivo = fopen(nombre_archivo,"r+b");
    FILE *archivoTemp;
    char* tempArch = "temp.dat";
    archivoTemp = fopen(tempArch,"w+b");
    T registro;
    while(fread(&registro,sizeof(T),1,archivo)){
        if(!(registro.id == objeto.id)){
            fwrite(&registro, sizeof(T), 1, archivoTemp);
        }
    }
    cerrar();
    fclose(archivoTemp);
    remove(nombre_archivo);
    rename(tempArch,nombre_archivo);
}
template<typename T>
void FileManager<T>::cerrar()
{

    fclose(archivo);
}


#endif 