#include"../File_Manager\file_manager.h"
#include<vector>
#include"../Producto/Producto.h"
#include<string>
#ifndef PRODUCTO_REPOSITORY_H
#define PRODUCTO_REPOSITORY_H
class ProductoRepository{
    private:
        std::vector<Producto> productos;
    public:
        char nombre_archivo[50];
        char nombre_archivo_cfg[50];
        FileManager<Producto> fileManager;
        FileManager<int> fileConfigManager;
        ProductoRepository(char nombre_archivo[50]):fileManager(nombre_archivo) , 
        fileConfigManager(nombre_archivo_cfg){
            strcpy(this->nombre_archivo, nombre_archivo);
            strcpy(this->nombre_archivo_cfg, nombre_archivo);
            strcat(this->nombre_archivo_cfg, "_cfg");
            fileConfigManager.setNombreArchivo(this->nombre_archivo_cfg);
            this->init();
        };
        void agregar(Producto producto);
        void init();
        void modificar(Producto producto);
        bool existeProducto(int id);
        void eliminar(int id);
        void generarReporte();
        int nuevaID();
        Producto obtenerProducto(int id);
};


#endif