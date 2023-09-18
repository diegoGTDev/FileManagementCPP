#include <stdio.h>
#include <fstream>
#include <string.h>
#include <iostream>
using namespace std;
#include "../Producto/Producto.h"
#include <typeinfo>
#include<vector>
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

template <class T>
class FileManager
{
private:
    char *nombre_archivo;
    FILE *archivo;

public:
    FileManager(char *nombre_archivo)
    {
        this->nombre_archivo = nombre_archivo;
    };

    void escribir(T objeto);
    void eliminar(T objeto);
    void modificarP(T producto);
    void modificar(T registro);
    vector<T> leerTodo();
    T leer();
    T obtenerObjeto(int id);
    bool existeArchivo();
    FILE *getArchivo();
    bool finalArchivo();
    void cerrar();
};

template<typename T>
vector<T> FileManager<T>::leerTodo(){
    vector<T> result;
    archivo = fopen(nombre_archivo, "rb");
    T registro;
    while (fread(&registro, sizeof(T), 1, archivo))
    {
        result.push_back(registro);
    }
    cerrar();
    return result;
}
template <typename T>
bool FileManager<T>::existeArchivo()
{
    archivo = fopen(nombre_archivo, "r+b");
    if (archivo == nullptr)
    {
        fclose(archivo);
        return false;
    }
    return true;
}
template <typename T>
FILE *FileManager<T>::getArchivo()
{
    return archivo;
}
template <typename T>
bool FileManager<T>::finalArchivo()
{
    return feof(archivo);
}
template <typename T>
void FileManager<T>::escribir(T objeto)
{
    if (!(existeArchivo()))
    {
        archivo = fopen(this->nombre_archivo, "w+b");
        fwrite(&objeto, sizeof(objeto), 1, archivo);
        fclose(archivo);
    }
    else
    {
        archivo = fopen(this->nombre_archivo, "a+b");
        fwrite(&objeto, sizeof(objeto), 1, archivo);
        fclose(archivo);
    }
}
template <typename T>
void FileManager<T>::modificarP(T producto)
{
    archivo = fopen(nombre_archivo, "rw+b");

    Producto registro;
    while (fread(&registro, sizeof(Producto), 1, archivo))
    {
        if (registro.id == producto.id)
        {
            // Modificar los campos del registro
            strcpy(registro.nombre, producto.nombre);
            registro.cantidad = producto.cantidad;
            registro.precio = producto.precio;
            strcpy(registro.lote, producto.lote);
            registro.categoria = producto.categoria;
            fwrite(&registro, sizeof(Producto), 1, archivo);
            break;
        }
    }

    fclose(archivo);
}
template<typename T>
void FileManager<T>::modificar(T registro){
    int id = registro;
    archivo = fopen(nombre_archivo, "r+b");
    fwrite(&id, sizeof(int), 1, archivo);
    cerrar();

}
template <typename T>
T FileManager<T>::leer()
{
    archivo = fopen(nombre_archivo, "rb");
    T result;
    fread(&result, sizeof(T), 1, archivo);
    cerrar();
    return result;
}
template <typename T>
void FileManager<T>::eliminar(T objeto)
{
    archivo = fopen(nombre_archivo, "r+b");
    FILE *archivoTemp;
    char *tempArch = "temp.dat";
    archivoTemp = fopen(tempArch, "w+b");
    T registro;
    while (fread(&registro, sizeof(T), 1, archivo))
    {
        if (!(registro.id == objeto.id))
        {
            fwrite(&registro, sizeof(T), 1, archivoTemp);
        }
    }
    cerrar();
    fclose(archivoTemp);
    remove(nombre_archivo);
    rename(tempArch, nombre_archivo);
}
template <typename T>
void FileManager<T>::cerrar()
{

    fclose(archivo);
}

#endif