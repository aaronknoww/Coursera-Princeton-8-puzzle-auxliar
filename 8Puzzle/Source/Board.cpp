#include "../Headers/Pch.h"
#include "../Headers/Board.h"

using namespace std;
Board::Board(int**& tiles, int n)
{
	this->n = n;
	col0 = 0; 
	fil0 = 0;
	gemelo = nullptr;
	sNeighbors = new vector<Board>();
	
	//Code to reserve memory to store tiles in order to create a board.
	this->tiles = new int*[n];
	for (int i = 0; i < n; i++)
		this->tiles[i] = new int[n];
	
	//To copy every tile
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			this->tiles[i][j] = tiles[i][j];


	

}

string Board::toString()
{
	string tablero;// = new string();
	tablero.append(to_string(n));
	tablero.append("\n");

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			tablero.append(to_string(tiles[i][j]));
			tablero.append(" ");
		}
		//tablero.replace(n - 1, n - 1, "");
		tablero.append("\n");

	}
	
	return tablero;
}

int Board::dimension()
{
	return n;
}

int Board::hamming()
{

	int count = 0;

	// To check every tile.
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			if (tiles[row][col] == 0)
				continue;

			if (!(tiles[row][col] == ((row * n) + col + 1)))// (row * n) + col + 1) To know which number corresponds to each position.
				count++;
		}

	}

	return count;
}

int Board::manhattan()
{
	int fila = 0;
	int columna = 0;
	int man = 0;
	
	// To check every tile.
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			if (tiles[row][col] == 0)
				continue;
			if (tiles[row][col] != ((row * n) + col + 1))//----> (row*n)+col+1) This formula is to know which number corresponds to the current cluster.
			{                                                //----> for example in matrix 3x3 [row = 0 col = 0] = 1; [row = 0 col = 1] = 2; [row = 0 col = 2] = 3;  
				fila = tiles[row][col] / n; //------------> To find the row it belongs to the current number
				columna = tiles[row][col] - (fila * n + 1);//-> To find the column it belongs to the current number
				man += abs(fila - row) + abs(columna - col);
			}
		}
	}

	return man;
}

bool Board::isGoal()
{
	for (int row = 0; row < this->n; row++)
	{
		for (int col = 0; col < this->n; col++)
		{
			if (tiles[row][col] == 0)
				continue;

			if (tiles[row][col] != ((row * this->n) + col + 1)) // (row * this->n) + col + 1) this is to know which number belong to the current cluster.
				return false;
		}

	}
	return true;
}

int** Board::getTile()
{
	return this->tiles;
}

bool Board::equals(Board& y)
{
	int** ty = y.getTile();

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (this->tiles[i][j] != ty[i][j])
				return false;
	return true;
}

vector<Board>& Board::neighbors()
{
	bool zero = false;

	for (int i = 0; i < this->n; i++)
	{
		for (int j = 0; j < this->n; j++)
		{
			if (tiles[i][j] == 0) // To find the position of number zero.
			{
				fil0 = i;
				col0 = j;
				zero = true;
				break;
			}

		}
		if (zero)
			break;
	}

	if (col0 - 1 >= 0)
		createNeighbor(fil0, col0 - 1);
	if (col0 + 1 < this->n)
		createNeighbor(fil0, col0 + 1);
	if (fil0 - 1 >= 0)
		createNeighbor(fil0 - 1, col0);
	if (fil0 + 1 < this->n)
		createNeighbor(fil0 + 1, col0);

	return *sNeighbors;

}

Board Board::twin()
{
	if (gemelo != nullptr)
		return *gemelo;

	int x;
	int y;
	int x2;
	int y2;
	srand(time(NULL));

	bool condition = true;
	do
	{
		x  = rand() % n; // A random number between 0 and n.
		y  = rand() % n;
		x2 = rand() % n;
		y2 = rand() % n;
		if (tiles[x][y] == 0 || tiles[x2][y2] == 0)
			condition = true;
		else if (tiles[x][y] == tiles[x2][y2])
			condition = true;
		else
			condition = false;
	} while (condition);

	int aux = 0;

	// Creating twin
	aux = tiles[x][y];
	tiles[x][y] = tiles[x2][y2];
	tiles[x2][y2] = aux;

	gemelo = new Board(tiles, n);

	// Returning tile to its intial state.

	tiles[x2][y2] = tiles[x][y];
	tiles[x][y] = aux;

	return *gemelo;
}

void Board::createNeighbor(int fila, int col) // fila, col --> Contain the position where the zero should be to crate a neighbor.
{
	
	tiles[fil0][col0] = tiles[fila][col];
	tiles[fila][col] = 0;
	sNeighbors->push_back(Board(tiles,n)); // TODO: VER QUE NO GENERE ERROR Y TENGA QUE MANDAR EL PUNTERO EN LUGAR DEL TABLERO.
	tiles[fila][col] = tiles[fil0][col0];
	tiles[fil0][col0] = 0;
	
}
