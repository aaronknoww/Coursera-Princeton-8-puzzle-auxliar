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
                   {4,2,0},
                   {7,6,5}};

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            tiles[i][j] = t[i][j];
    
    

    Board tablero(tiles,n);
    
    
  
    std::cout << tablero.toString() << "\n";
    std::cout << tablero.hamming() << "\n";
    std::cout << tablero.manhattan() << "\n";
    
    vector<Board> tabs = tablero.neighbors();
    std::cout << "TABLERO\n" << tablero.toString() << "\n";
    for (int i = 0; i < tabs.size(); i++)
        cout << tabs[i].toString();
    std::cout << "TABLERO debug\n" << tablero.toString() << "\n";
    std::cout << "TABLERO GEMELO\n" << tablero.twin().toString() << "\n";
}


