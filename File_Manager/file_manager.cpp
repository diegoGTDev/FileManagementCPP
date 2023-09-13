#include "file_manager.h"
#include "../Producto/Producto.h"

template <typename T>
bool FileManager<T>::existeArchivo()
{
    archivo = fopen(nombre_archivo,"r");
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
template<typename T>
void FileManager<T>::modificar(T producto)
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
template<typename T>
T FileManager<T>::leer(T producto)
{
    archivo = fopen(nombre_archivo,"rt");
    fread(&producto,sizeof(producto),1,archivo);
    cerrar();
    return producto;
}
template<typename T>
void FileManager<T>::eliminar(T objeto){
    archivo = fopen(nombre_archivo,"rt");
    T registro;
    while(fread(&registro,sizeof(T),1,archivo)){
        if(registro.id == objeto.id){
            fseek(archivo, -sizeof(T), SEEK_CUR);
            fwrite(&registro, sizeof(T), 1, archivo);
            break;
        }
    }
    cerrar();
    cout<<"obj: "<<objeto.nombre<<endl;
}
template<typename T>
void FileManager<T>::cerrar()
{

    fclose(archivo);
}