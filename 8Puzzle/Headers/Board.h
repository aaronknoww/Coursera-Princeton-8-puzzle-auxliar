#pragma once
#include "Pch.h"

using namespace std;

class Board
{
private:

	int** tiles;
	int col0;
	int fil0;
	Board* gemelo;
	stack<Board>* sNeighbors;

public:
	
	Board(int **& tiles, int n);
	/*string toString();
	int dimension();
	int hamming();
	int manhattan();
	bool isGoal();
	bool equals(Board y);
	stack<Board>& neighbors();
	Board twin();*/

	//~Board();
	

private:

	//void createNeighbor(int fila, int col);


};
