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
    stack<Board*>* solutionSk() { return solutionStk; }

private:
    class NodeBoard
    {
    private:
        Board* board;
        NodeBoard* father;
        int hamming;
        int manhattan;
        bool visited;
    public:
        NodeBoard();
        NodeBoard(Board* board);
        NodeBoard(Board* board, NodeBoard* father);
        Board* getBoard() const { return board; }
        int getHamming() const { return hamming; }
        int getManhattan()const { return manhattan; }
        int getPrority() { return hamming + manhattan; }
        bool isVisited() { return visited; }
        NodeBoard* getFather()const { return this->father; }
        void setFather(NodeBoard* father) { this->father = father; }
        void setVisited(bool visited) { this->visited = visited; }
        bool operator==(const NodeBoard& obj) const
        {      
            NodeBoard copy = obj;
            return this->board->equals(*copy.getBoard());
        };
        bool operator<(const NodeBoard& obj) const 
        {
            NodeBoard copy = obj;
            return (this->getBoard()->hamming() + this->getBoard()->manhattan()) < (copy.getBoard()->hamming() + copy.getBoard()->manhattan());
        };
        

    };
    class mycomparison
    {
        
    public:
        
        bool operator() (NodeBoard* &lhs, NodeBoard* &rhs) const
        {
            ////CODIOG PARA DEPURAR TODO: borrar depues de depurar.
            //cout << "\nTablero Izquierdo\n";
            //cout << lhs.getBoard()->toString() << endl;
            //cout << "ham: " << lhs.getBoard()->hamming() << endl;
            //cout << "man: " << lhs.getBoard()->manhattan() << endl;
            //cout << "********************\n";
            ////----------------------------
            //cout << "\nTablero Derecho\n";
            //cout << rhs.getBoard()->toString() << endl;
            //cout << "ham: " << rhs.getHamming() << endl;
            //cout << "man: " << rhs.getManhattan() << endl;
            //cout << "********************\n";
            ////----------------------------
            return (lhs->getBoard()->hamming() + lhs->getBoard()->manhattan()) > (rhs->getBoard()->hamming() + rhs->getBoard()->manhattan());
        }
    };
    class CompByBoard
    {
        //
    public:

        bool operator() (const NodeBoard &lhs, const NodeBoard &rhs) const
        {         
            return (lhs.getManhattan() + lhs.getHamming()) < (rhs.getHamming() + rhs.getManhattan());
        }
    };
  
    queue<Board*>* solutionQue; // To store only solution boards.
    stack<Board*>* solutionStk;
    priority_queue<NodeBoard*, vector<NodeBoard*>, mycomparison>* priorityPQ;
    priority_queue<NodeBoard*, vector<NodeBoard*>, mycomparison>* twinPQ;
    multiset<NodeBoard,CompByBoard>* nodesCreated;// To store every node created.
    multiset<NodeBoard,CompByBoard>* twinsCreated;// To store every node created.
    int move;
    bool solvable;

};

