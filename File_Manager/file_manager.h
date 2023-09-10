#include<stdio.h>
#include<fstream>
#include"../Producto/Producto.h"

#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

class FileManager{
    private:
        char* nombre_archivo;
        FILE *archivo;
    public:
        FileManager(char* nombre_archivo){
            this->nombre_archivo = nombre_archivo;
        };

        void escribir(Producto objeto);
        void modificar(Producto producto);
        Producto leer(Producto producto);
        Producto obtenerObjeto(int id);
        bool existeArchivo();
        FILE* getArchivo();
        bool finalArchivo();
        void cerrar();
};




#endif 