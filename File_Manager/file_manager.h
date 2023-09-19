#include <stdio.h>
#include <fstream>
#include <string.h>
#include <iostream>
#include "../Producto/Producto.h"
#include <typeinfo>
#include<vector>
using namespace std;
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

template <class T>
class FileManager
{
private:
    char nombre_archivo[50];
    FILE *archivo;

public:
    FileManager(char nombre_archivo[50])
    {
        strcpy(this->nombre_archivo, nombre_archivo);
        strcat(this->nombre_archivo, ".dat");
    };

    void escribir(T registro);
    void eliminar(T registro);
    void modificarP(T registro);
    void modificarCFG(T registro);
    vector<T> leerTodo();
    T leer();
    T obtenerObjeto(int id);
    bool existeArchivo();
    FILE *getArchivo();
    void setNombreArchivo(char nombre_archivo[50]);
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
        cerrar();
        return false;
    }
    cerrar();
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
void FileManager<T>::escribir(T registro)
{
    if (!(existeArchivo()))
    {
        archivo = fopen(this->nombre_archivo, "w+b");
        fwrite(&registro, sizeof(registro), 1, archivo);
        cerrar();
    }
    else
    {
        archivo = fopen(this->nombre_archivo, "a+b");
        fwrite(&registro, sizeof(registro), 1, archivo);
        cerrar();
    }
}
template <typename T>
void FileManager<T>::modificarP(T registro)
{
    archivo = fopen(nombre_archivo, "rw+b");

    Producto registroTemp;
    while (fread(&registro, sizeof(registro), 1, archivo))
    {
        if (registro.id == registro.id)
        {
            // Modificar los campos del registro
            strcpy(registroTemp.nombre, registro.nombre);
            registroTemp.cantidad = registro.cantidad;
            registroTemp.precio = registro.precio;
            strcpy(registroTemp.lote, registro.lote);
            registroTemp.categoria = registro.categoria;
            fwrite(&registroTemp, sizeof(Producto), 1, archivo);
            break;
        }
    }

    cerrar();
}
template<typename T>
void FileManager<T>::modificarCFG(T registro){

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
template <class T>
void FileManager<T>::setNombreArchivo(char nombre_archivo[50])
{
    strcpy(this->nombre_archivo, nombre_archivo);
    strcat(this->nombre_archivo, ".dat");
}
template <typename T>
void FileManager<T>::eliminar(T registro)
{
    archivo = fopen(nombre_archivo, "r+b");
    FILE *archivoTemp;
    char *tempArch = "temp.dat";
    archivoTemp = fopen(tempArch, "w+b");
    T registroTemp;
    while (fread(&registroTemp, sizeof(T), 1, archivo))
    {
        if (!(registroTemp.id == registro.id))
        {
            fwrite(&registroTemp, sizeof(T), 1, archivoTemp);
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