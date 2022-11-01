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
    NodeBoard* aux = nullptr;
    NodeBoard* nTop;

    bool goal = false;
    move = 0;
    solvable = false;
    solutionQue = new queue<Board*>;
    nodesCreated = new multiset<NodeBoard,CompByBoard>;
    vector<Board*> neighbors;
    
    if (initial->isGoal())
    {
        solutionQue->push(initial);
        return;
    }

    solutionQue->push(initial);
    aux = new NodeBoard(initial, nullptr);
    priorityPQ = new priority_queue<NodeBoard*, vector<NodeBoard*>, mycomparison>();
    priorityPQ->push(aux);
    nodesCreated->insert(*aux);

    
    //CODIOG PARA DEPURAR TODO: borrar depues de depurar.
    cout << "Tablero inicial\n";
    cout << initial->toString() << endl;
    cout << "********************\n";
    //----------------------------

    Board* board = nullptr;
    Board* frt = nullptr;
    frt = solutionQue->back();
    
    do
    {
             
        node = priorityPQ->top();
        priorityPQ->pop();

        //CODIOG PARA DEPURAR TODO: borrar depues de depurar.
        cout << "Tablero PADRE\n";
        cout << node->getBoard()->toString() << endl;
        cout << "ham: " << node->getHamming() << endl;
        cout << "man: " << node->getManhattan() << endl;
        cout << "********************\n";
        //----------------------------

        int vecino = 0; // TODO: borrar despues de depurar.
        
        neighbors = node->getBoard()->neighbors();
                
        cout << "ULTIMO EN ENTRAR " <<  endl;
        cout << frt->toString() << endl;

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
                      
            //CODIGO PARA DEPURAR TODO: BORRAR DEPUES DE DEPURAR ejecutar esta parte
            vecino++;
            cout << "Vecino " << vecino << endl;
            cout << neighbors[i]->toString() << endl;
            //cout << "P " << board->toString() << endl;
            cout << "ham: " << neighbors[i]->hamming() << endl;
            cout << "man: " << neighbors[i]->manhattan() << endl;
            cout << "********************" << endl;
            board = nullptr;
            aux = nullptr;
        }

        cout << "|||||||||||||||||||||||||||" << endl;
        cout << "\nTABLEROS DE TRABAJO" << endl;
        nTop = priorityPQ->top();
        //CODIOG PARA DEPURAR TODO: borrar depues de depurar.
        cout << "\nTablero padre\n";
        cout << node->getBoard()->toString() << endl;
        cout << "ham: " << node->getBoard()->hamming() << endl;
        cout << "man: " << node->getBoard()->manhattan() << endl;
        cout << "********************\n";
        //----------------------------
        cout << "\nVecino con menor prioridad\n";
        cout << nTop->getBoard()->toString() << endl;
        cout << "ham: " << nTop->getHamming() << endl;
        cout << "man: " << nTop->getManhattan() << endl;
        cout << "********************\n";
        //----------------------------
                
        move++;
        goal = nTop->getBoard()->isGoal();
        //TODO: Borrar despues de depurar.
        frt = solutionQue->back();
        solutionQue->push(nTop->getBoard());
        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (priorityPQ->empty())
        {
            solvable = false;
            return;
        }
    } while (!goal);

    solvable = true;
    delete solutionQue;
    solutionQue = nullptr;
    solutionQue = new queue<Board*>;
    solutionStk = new stack<Board*>;
    while (nTop != nullptr)
    {
        solutionQue->push(nTop->getBoard());
        solutionStk->push(nTop->getBoard());
        nTop = nTop->getFather();
        

    }
    move = solutionQue->size();
    //TODO: DEPURAR PARA VER SI FUNICIONA.

}

