#include"../File_Manager\file_manager.h"
#include"../Producto/Producto.h"
#ifndef PRODUCTO_REPOSITORY_H
#define PRODUCTO_REPOSITORY_H
class ProductoRepository{

    public:
        char* nombre_archivo;
        FileManager fileManager;
        ProductoRepository(char* nombre_archivo):fileManager(nombre_archivo) , nombre_archivo(nombre_archivo){
            FileManager fileManager(nombre_archivo);
        };
        void agregar(Producto producto);
        void modificar(Producto producto);
        void generarReporte();
        Producto obtenerProducto(int id);
};


#endif