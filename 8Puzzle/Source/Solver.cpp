#include "../Headers/Pch.h"
#include "../Headers/Solver.h"

Solver::NodeBoard::NodeBoard(Board* board)
{    
    this->board = board;
    this->hamming = board->hamming();
    this->manhattan = board->manhattan();    
}

Solver::Solver(Board *initial)
{
    NodeBoard node = nullptr;
    solvable = false;
    solutionQue = new queue<Board>;
    if (initial->isGoal())
    {
        solutionQue->push(initial);
        return;
    }

    priorityPQ = new priority_queue<NodeBoard, vector<NodeBoard>, mycomparison>;
    priorityPQ->push(NodeBoard(initial));
    
    

    do
    {

        node = priorityPQ->top();
        solutionQue->push(node.getBoard()); 

    //TODO: AQUI ME QUEDE

        for (var nei : node.board.neighbors())
            priorityPQ.insert(new NodeBoard(nei)); // To insert every neighbor in the preority queue

        if ((node.hamming + node.manhattan) < (priorityPQ.min().hamming + priorityPQ.min().manhattan))
            return;
        moves++;

    } while (!node.board.isGoal());

    solvable = true;
    //TODO: DEPURAR PARA VER SI FUNICIONA.




}
