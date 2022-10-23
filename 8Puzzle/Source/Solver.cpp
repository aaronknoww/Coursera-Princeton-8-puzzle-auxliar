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
}

Solver::Solver(Board *initial)
{
    priorityPQ = nullptr;
    NodeBoard node;
    NodeBoard nTop;
    bool goal = false;
    move = 0;
    solvable = false;
    solutionQue = new queue<Board*>;
    vector<Board*> neighbors;
    if (initial->isGoal())
    {
        solutionQue->push(initial);
        return;
    }

    solutionQue->push(initial);
    priorityPQ = new priority_queue<NodeBoard, vector<NodeBoard>, mycomparison>();
    priorityPQ->push(NodeBoard(initial));
    
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
        cout << node.getBoard()->toString() << endl;
        cout << "ham: " << node.getHamming() << endl;
        cout << "man: " << node.getManhattan() << endl;
        cout << "********************\n";
        //----------------------------

        int vecino = 0; // TODO: borrar despues de depurar.
        
        neighbors = node.getBoard()->neighbors();
                
        cout << "ULTIMO EN ENTRAR " <<  endl;
        cout << frt->toString() << endl;

        for (size_t i = 0; i < neighbors.size(); i++)
        {
            board = neighbors[i];
            if (board->equals(*frt))// To don't store the father board.
                continue;

            priorityPQ->push(NodeBoard(board)); // To insert every neighbor in the preority queue, but need to be a board pointer.
            //priorityPQ->push(neighbors[i]); TODO: REVISAR SI PUEDO QUITAR LA VARIABLE board

            //CODIGO PARA DEPURAR TODO: BORRAR DEPUES DE DEPURAR ejecutar esta parte
            vecino++;
            cout << "Vecino " << vecino << endl;
            cout << neighbors[i]->toString() << endl;
            //cout << "P " << board->toString() << endl;
            cout << "ham: " << neighbors[i]->hamming() << endl;
            cout << "man: " << neighbors[i]->manhattan() << endl;
            cout << "********************" << endl;
            board = nullptr;
        }

        cout << "|||||||||||||||||||||||||||" << endl;
        cout << "\nTABLEROS DE TRABAJO" << endl;
        nTop = priorityPQ->top();
        //CODIOG PARA DEPURAR TODO: borrar depues de depurar.
        cout << "\nTablero padre\n";
        cout << node.getBoard()->toString() << endl;
        cout << "ham: " << node.getBoard()->hamming() << endl;
        cout << "man: " << node.getBoard()->manhattan() << endl;
        cout << "********************\n";
        //----------------------------
        cout << "\nVecino con menor prioridad\n";
        cout << nTop.getBoard()->toString() << endl;
        cout << "ham: " << nTop.getHamming() << endl;
        cout << "man: " << nTop.getManhattan() << endl;
        cout << "********************\n";
        //----------------------------

        //if ((node.getHamming() + node.getManhattan()) < (nTop.getHamming() + nTop.getManhattan())) // To comper Board father with his neighbor
        //    return; //TODO: CHECAR SI SALE DEL PROGRAMA PORQUE NO TIENE SOLUCION.

        move++;
        goal = nTop.getBoard()->isGoal();
        frt = solutionQue->back();
        solutionQue->push(nTop.getBoard());

    } while (!goal && move < 100);

    solvable = true;
    //TODO: DEPURAR PARA VER SI FUNICIONA.

}
