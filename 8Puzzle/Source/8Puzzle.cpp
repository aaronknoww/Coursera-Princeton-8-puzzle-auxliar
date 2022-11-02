#include "../Headers/Pch.h"
#include "../Headers/Board.h"
#include "../Headers/Solver.h"
// 8Puzzle.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

using namespace std;
class mycomparison
{
    bool reverse;
public:
  
    bool operator() (int& lhs, int& rhs) const
    {
        if (reverse) return (lhs > rhs);
        else return (lhs < rhs);
    }
};

class NodeBoard2
{
private:
    Board* board;
    int hamming;
    int manhattan;
public:
    NodeBoard2(Board* board)
    {

        this->board = board;
        this->hamming = board->hamming();
        this->manhattan = board->manhattan();

    }
    Board* getBoard() { return board; }
    int getHamming() { return hamming; }
    int getManhattan() { return manhattan; }
    int getPrority() { return hamming + manhattan; }


};

class MycomparisonB
{

public:

    bool operator() (NodeBoard2* lhs, NodeBoard2* rhs) const
    {
        return lhs->getPrority() >= rhs->getPrority();
    }
};

int main()
{
    /*int n = 3;
    int** tiles = new int* [n];
    int** tiles2 = new int* [n];
    */
    int n = 4;
    int** tiles = new int* [n];
    int** tiles2 = new int* [n];

    for (int i = 0; i < n; i++)
    {
        tiles[i] = new int[n];
        tiles2[i] = new int[n];
    }

    //int t[3][3] = {{1,2,3},
    //               {4,0,5},
    //               {7,8,6} };

    /*
    int t[3][3] = {{8,6,7},
                   {2,5,4},
                   {3,0,1} };*/
    
    // //int t[3][3] = {{8,6,7},
    //                 {2,0,4},
    //                 {3,5,1} };

    int t[4][4] = { {0, 12, 9,13},
                    {15, 11, 10, 14},
                    {3, 7, 5, 6},
                    {4, 8, 2, 1} };
    

 /*   int t[3][3] = {{1,2,3},
                   {0,5,6},
                   {4,7,8} };*/

    
    // No tiene solucion.
    /*  int t[3][3] = {{1,2,3},
                      {4,6,5},
                      {7,8,0} };
      */
      
      // No tiene solucion.
  /*    int t[3][3] = {{8,6,7},
                      {2,5,4},
                      {1,3,0} };*/



    int d[3][3] = {{1,8,3},
                   {4,0,2},
                   {7,6,5} };

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            tiles[i][j] = t[i][j];
            tiles2[i][j] = d[i][j];
        }

    
    //Board * tablero = new Board(tiles, n);
    Board * tablero = new Board(tiles, n);
    Solver sol(tablero);
    cout << "Tiene solucion? " << sol.isSolvable()<<endl;
    int paso = 1;
   
    while (!sol.solutionSk()->empty())
    {
        cout << "Paso: " << paso << endl;
        cout << "Tablero" << endl;
        cout << sol.solutionSk()->top()->toString() << endl;
        sol.solutionSk()->pop();
        paso++;
    }
    while(!sol.solution()->empty())
   {
       cout << "Paso: " << paso << endl;
       cout << "Tablero" << endl;
       cout << sol.solution()->front()->toString() << endl;
       sol.solution()->pop();
       paso++;
   }
    Board * tablero2 = new Board(tiles2, n);
    
    int myints[] = { 10,60,50,20 };

    //priority_queue<int, std::vector<int>, mycomparison> mypq(myints, myints + 4, mycomparison(true));
    priority_queue<int, std::vector<int>, mycomparison> mypq;
    mypq.push(15);
    mypq.push(13);
    mypq.push(20);
    mypq.push(25);

    
    priority_queue<NodeBoard2*, vector<NodeBoard2*>, MycomparisonB> *priorityPQ = new priority_queue<NodeBoard2*, vector<NodeBoard2*>, MycomparisonB>;
    //priorityPQ.push(new NodeBoard(tablero));
    NodeBoard2 *node = new NodeBoard2(tablero);
    NodeBoard2 *node2 = new NodeBoard2(tablero2);
    priorityPQ->push(node);
    priorityPQ->push(node2);


    while (! priorityPQ->empty())
    {
        
        cout << priorityPQ->top()->getBoard()->toString()<<endl;
        cout << priorityPQ->top()->getBoard()->hamming()<<endl;
        cout << priorityPQ->top()->getBoard()->manhattan()<<endl;
        
        priorityPQ->pop();

    }

 /*   int n = 3;
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
    std::cout << "TABLERO GEMELO\n" << tablero.twin().toString() << "\n";*/
}


