#include "../Headers/Pch.h"
#include "../Headers/Board.h"
// 8Puzzle.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

//#include <iostream>

int main()
{
    int n = 3;
    int** tiles = new int* [n];
    
    for (int i = 0; i < n; i++)
        tiles[i] = new int[n];

    int t[3][3] = {{8,1,3},
                  {4,0,2},
                  {7,6,5}};

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            tiles[i][j] = t[i][j];
    
    

    Board tablero(tiles,n);
    std::cout << "Hello World!\n";
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
