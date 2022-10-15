#pragma once
#include "Board.h"

using namespace std;
class Solver
{
public:
    
    Solver(Board *initial);
    
    // is the initial board solvable? (see below)
    bool isSolvable();

    // min number of moves to solve initial board; -1 if unsolvable
    int moves();
    
    // sequence of boards in a shortest solution; null if unsolvable
    queue<Board> solution();

private:
    class NodeBoard
    {
    private:
        Board* board;
        int hamming;
        int manhattan;
    public:
        NodeBoard(Board* board);
        Board* getBoard() { return board; }
        int getHamming() { return hamming; }
        int getManhattan() { return manhattan; }
        int getPrority() { return hamming + manhattan; }


    };
    class mycomparison
    {
        
    public:
        
        bool operator() (NodeBoard& lhs, NodeBoard& rhs) const
        {
            return lhs.getPrority() >= rhs.getPrority();
        }
    };
    //int moves;
    queue<Board*>* solutionQue;
    bool solvable;
    priority_queue<NodeBoard, vector<NodeBoard>, mycomparison>* priorityPQ;

    

};

