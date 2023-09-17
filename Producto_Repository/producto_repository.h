#include"../File_Manager\file_manager.h"
#include<vector>
#include"../Producto/Producto.h"
#ifndef PRODUCTO_REPOSITORY_H
#define PRODUCTO_REPOSITORY_H
class ProductoRepository{
    private:
        std::vector<Producto> productos;
    public:
        char* nombre_archivo;
        FileManager<Producto> fileManager;
        ProductoRepository(char* nombre_archivo):fileManager(nombre_archivo) , nombre_archivo(nombre_archivo){
            this->init();
        };
        void agregar(Producto producto);
        void init();
        void modificar(Producto producto);
        bool existeProducto(int id);
        void eliminar(int id);
        void generarReporte();
        int obtenerCantidadProductos();
        Producto obtenerProducto(int id);
};


#endif