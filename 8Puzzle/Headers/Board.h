#pragma once
#include "Pch.h"

using namespace std;

class Board
{
private:

	int** tiles;
	int n;
	int col0;
	int fil0;
	Board* gemelo;
	vector<Board>* sNeighbors;

public:
	
	Board(int **& tiles, int n);
	string toString();
	int dimension();
	int hamming();
	int manhattan();
	bool isGoal();
	int** getTile();
	bool equals(Board &y);
	vector<Board>& neighbors();
	Board twin();

	//~Board();
	

private:

	void createNeighbor(int fila, int col);


};
