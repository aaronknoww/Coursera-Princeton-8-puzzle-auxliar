#include "../Headers/Pch.h"
#include "../Headers/Solver.h"

using namespace std;

Solver::NodeBoard::NodeBoard()
{
    board = nullptr;
    hamming = 0;
    manhattan = 0;
}

Solver::NodeBoard::NodeBoard(Board* board)
{    
    this->board = board;
    this->father = nullptr;
    this->hamming = this->board->hamming();
    this->manhattan = this->board->manhattan();
    visited = false;
}

Solver::NodeBoard::NodeBoard(Board* board, NodeBoard* father)
{
    this->board = board;
    this->father = father;
    this->hamming = this->board->hamming();
    this->manhattan = this->board->manhattan();
    visited = false;
}

Solver::Solver(Board *initial)
{
    priorityPQ = nullptr;
    nodesCreated = nullptr;
    NodeBoard* node = nullptr;
    NodeBoard* twinNode = nullptr;
    NodeBoard* aux = nullptr;
    NodeBoard* twinAux = nullptr;
    NodeBoard* nTop;
    NodeBoard* twinTop;
    move = 0;
    solvable = false;
    nodesCreated = new multiset<NodeBoard,CompByBoard>;
    twinsCreated = new multiset<NodeBoard, CompByBoard>;
    vector<Board*> neighbors;
    vector<Board*> twinNeighbors;
    
    if (initial->isGoal())
    {        
        solvable = true;
        return;
    }
        
    aux = new NodeBoard(initial, nullptr);
    twinAux = new NodeBoard(initial->twin(), nullptr);
    priorityPQ = new priority_queue<NodeBoard*, vector<NodeBoard*>, mycomparison>();
    twinPQ = new priority_queue<NodeBoard*, vector<NodeBoard*>, mycomparison>();
    priorityPQ->push(aux);
    twinPQ->push(twinAux);
    nodesCreated->insert(*aux);
    twinsCreated->insert(*twinAux);

    do
    {
             
        node = priorityPQ->top();
        priorityPQ->pop();
        twinNode = twinPQ->top();
        twinPQ->pop();
        neighbors = node->getBoard()->neighbors();
        twinNeighbors = twinNode->getBoard()->neighbors();
    
        for (size_t i = 0; i < neighbors.size(); i++)
        {
            
            if (node->getFather() && (node->getFather()->getBoard()->equals(*neighbors[i])))
                continue;

            aux = new NodeBoard(neighbors[i], node);
            
            for (auto it = nodesCreated->begin(); it != nodesCreated->end(); ++it)
            {
                if (aux && *aux == *it)
                {
                    delete aux;
                    aux = nullptr;
                    break;
                }
            }
            if (aux == nullptr)
                continue;
            
            nodesCreated->insert(*aux);
            priorityPQ->push(aux); // To insert every neighbor in the preority queue, but need to be a board pointer.
            aux = nullptr;
        }
        
        
        // |||||||||||| TWIN AREA |||||||||||||||||||||


        for (size_t i = 0; i < twinNeighbors.size(); i++)
        {

            if (twinNode->getFather() && (twinNode->getFather()->getBoard()->equals(*twinNeighbors[i])))
                continue;

            twinAux = new NodeBoard(twinNeighbors[i], twinNode);

            for (auto it = twinsCreated->begin(); it != twinsCreated->end(); ++it)
            {
                if (twinAux && *twinAux == *it)
                {
                    delete twinAux;
                    twinAux = nullptr;
                    break;
                }
            }
            if (twinAux == nullptr)
                continue;


            twinsCreated->insert(*twinAux);
            twinPQ->push(twinAux); // To insert every neighbor in the preority queue, but need to be a board pointer.


            twinAux = nullptr;
        }

            

        
        nTop = priorityPQ->top();
        twinTop = twinPQ->top();
                        
        move++;       
        
    } while ((!nTop->getBoard()->isGoal()) && (!twinTop->getBoard()->isGoal()));

    
    if (nTop->getBoard()->isGoal())
    {
        solutionStk = new stack<Board*>;
        while (nTop != nullptr)
        {
            solutionStk->push(nTop->getBoard());
            nTop = nTop->getFather();
        }
        move = solutionStk->size();
        solvable = true;
        return;

    }
    else
    {
        move = -1;
        solvable = false;
        return;
    }
    

}

