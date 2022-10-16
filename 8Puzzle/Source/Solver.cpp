#include "../Headers/Pch.h"
#include "../Headers/Solver.h"

Solver::NodeBoard::NodeBoard()
{
    board = nullptr;
    hamming = 0;
    manhattan = 0;
}

Solver::NodeBoard::NodeBoard(Board* board)
{    
    this->board = board;
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
    
    do
    {
        //TODO: PONER TODOS LOS TABLEROS EN MEMORIA HEAP.
        //solutionQue->push(node.getBoard());
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
        
        vector<Board*> neighbors = node.getBoard()->neighbors();
        for (size_t i = 0; i < neighbors.size(); i++)
        {
            board = neighbors[i];
            priorityPQ->push(NodeBoard(board)); // To insert every neighbor in the preority queue, but need to be a board pointer.

            //CODIGO PARA DEPURAR TODO: BORRAR DEPUES DE DEPURAR ejecutar esta parte
            vecino++;
            cout << "Vecino " << vecino << endl;
            cout << neighbors[i]->toString() << endl;
            //cout << "P " << board->toString() << endl;
            cout << "ham: " << neighbors[i]->hamming() << endl;
            cout << "man: " << neighbors[i]->manhattan() << endl;
            cout << "********************";
            board = nullptr;
        }

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

        if ((node.getHamming() + node.getManhattan()) < (nTop.getHamming() + nTop.getManhattan())) // To comper Board father with his neighbor
            return; //TODO: CHECAR SI SALE DEL PROGRAMA PORQUE NO TIENE SOLUCION.

        move++;
        goal = nTop.getBoard()->isGoal();
        solutionQue->push(nTop.getBoard());

    } while (!goal);

    solvable = true;
    //TODO: DEPURAR PARA VER SI FUNICIONA.




}
