#pragma once
#include "Board.h"

using namespace std;
class Solver
{
public:
    
    Solver(Board *initial);
    
    // is the initial board solvable? (see below)
    bool isSolvable() { return solvable; }

    // min number of moves to solve initial board; -1 if unsolvable
    int moves() { return move; }
    
    // sequence of boards in a shortest solution; null if unsolvable
    queue<Board*>* solution() { return solutionQue; }

private:
    class NodeBoard
    {
    private:
        Board* board;
        int hamming;
        int manhattan;
    public:
        NodeBoard();
        NodeBoard(Board* board);
        Board* getBoard() { return board; }
        int getHamming() { return hamming; }
        int getManhattan() { return manhattan; }
        int getPrority() { return hamming + manhattan; }


    };
    class mycomparison
    {
        
    public:
        
        bool operator() (NodeBoard &lhs, NodeBoard &rhs) const
        {
            //CODIOG PARA DEPURAR TODO: borrar depues de depurar.
            cout << "\nTablero Izquierdo\n";
            cout << lhs.getBoard()->toString() << endl;
            cout << "ham: " << lhs.getBoard()->hamming() << endl;
            cout << "man: " << lhs.getBoard()->manhattan() << endl;
            cout << "********************\n";
            //----------------------------
            cout << "\nTablero Derecho\n";
            cout << rhs.getBoard()->toString() << endl;
            cout << "ham: " << rhs.getHamming() << endl;
            cout << "man: " << rhs.getManhattan() << endl;
            cout << "********************\n";
            //----------------------------
            return (lhs.getBoard()->hamming() + lhs.getBoard()->manhattan()) > (rhs.getBoard()->hamming() + rhs.getBoard()->manhattan());
        }
    };
    int move;
    queue<Board*>* solutionQue;
    bool solvable;
    priority_queue<NodeBoard, vector<NodeBoard>, mycomparison>* priorityPQ;

    

};

