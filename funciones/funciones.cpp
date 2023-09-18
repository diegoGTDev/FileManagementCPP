#include<windows.h>
#include"funciones.h"
void gotoxy(int x, int y){
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(handle,coord);
}
void cambiarColor(int color){
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, color);
}