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

    bool goal = false;
    move = 0;
    solvable = false;
    solutionQue = new queue<Board*>;// TODO: REPLACE FOR STACK.
    nodesCreated = new multiset<NodeBoard,CompByBoard>;
    twinsCreated = new multiset<NodeBoard, CompByBoard>;
    vector<Board*> neighbors;
    vector<Board*> twinNeighbors;
    
    if (initial->isGoal())
    {
        solutionQue->push(initial);
        solvable = true;
        return;
    }

    solutionQue->push(initial);
    aux = new NodeBoard(initial, nullptr);
    twinAux = new NodeBoard(initial->twin(), nullptr);
    priorityPQ = new priority_queue<NodeBoard*, vector<NodeBoard*>, mycomparison>();
    twinPQ = new priority_queue<NodeBoard*, vector<NodeBoard*>, mycomparison>();
    priorityPQ->push(aux);
    twinPQ->push(twinAux);
    nodesCreated->insert(*aux);
    twinsCreated->insert(*twinAux);


    
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
        twinNode = twinPQ->top();
        twinPQ->pop();
        //CODIOG PARA DEPURAR TODO: borrar depues de depurar.
        cout << "Tablero PADRE\n";
        cout << node->getBoard()->toString() << endl;
        cout << "ham: " << node->getHamming() << endl;
        cout << "man: " << node->getManhattan() << endl;
        cout << "********************\n";
        //----------------------------

        int vecino = 0; // TODO: borrar despues de depurar.
        
        neighbors = node->getBoard()->neighbors();
        twinNeighbors = twinNode->getBoard()->neighbors();
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

            

        cout << "|||||||||||||||||||||||||||" << endl;
        cout << "\nTABLEROS DE TRABAJO" << endl;
        nTop = priorityPQ->top();
        twinTop = twinPQ->top();
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
    } while ((!nTop->getBoard()->isGoal()) && (!twinTop->getBoard()->isGoal()));

    delete solutionQue;
    solutionQue = nullptr;
    solutionQue = new queue<Board*>;
    
    if (nTop->getBoard()->isGoal())
    {
        solutionStk = new stack<Board*>;
        while (nTop != nullptr)
        {
            solutionQue->push(nTop->getBoard());
            solutionStk->push(nTop->getBoard());
            nTop = nTop->getFather();
        

        }
        move = solutionQue->size();
        solvable = true;
        return;

    }
    else
    {
        move = -1;
        solvable = false;
        return;
    }
    //TODO: DEPURAR PARA VER SI FUNICIONA.

}

