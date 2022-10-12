#include "../Headers/Pch.h"
#include "../Headers/Board.h"

Board::Board(int**& tiles, int n)
{
	col0 = 0; 
	fil0 = 0;
	gemelo = nullptr;
	sNeighbors = new stack<Board>();

	//Code to reserve memory to store tiles in order to create a board.
	this->tiles = new int*[n];
	for (int i = 0; i < n; i++)
		this->tiles[i] = new int[n];
	
	//To copy every tile
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			this->tiles[i][j] = tiles[i][j];


	

}
