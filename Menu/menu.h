#include"../Producto/Producto.h"
#include"../Producto_Repository/producto_Repository.h"
void imprimirMenu();
Categoria seleccionarCategoria(int x, int y);
bool menu_agregarProductos(ProductoRepository& productoRepository);
void menu_modificarProductos(ProductoRepository& productoRepository);
void menu_eliminarProducto(ProductoRepository& productoRepository);
void menu_generarReporte(ProductoRepository& productoRepository);