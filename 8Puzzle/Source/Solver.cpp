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
    move = 0;
    solvable = false;
    solutionQue = new queue<Board*>;
    if (initial->isGoal())
    {
        solutionQue->push(initial);
        return;
    }
    priorityPQ = new priority_queue<NodeBoard, vector<NodeBoard>, mycomparison>();
    priorityPQ->push(NodeBoard(initial));
    
    //CODIOG PARA DEPURAR TODO: borrar depues de depurar.
    cout << "Tablero inicial\n";
    cout << initial->toString() << endl;
    cout << "********************\n";
    //----------------------------
    do
    {

        node = priorityPQ->top();
        priorityPQ->pop();
        solutionQue->push(node.getBoard());

        int vecino = 0; // TODO: borrar despues de depurar.
        Board* board = nullptr;
        //Board* n1 = &prueba[1];
        //Board* n2 = &prueba[2];
        //priorityPQ->push(NodeBoard(n1));
        //priorityPQ->push(NodeBoard(n2));

        auto prueba = node.getBoard()->neighbors();
        for (size_t i = 0; i < prueba.size(); i++)
        {
            board = &prueba[i];
            priorityPQ->push(NodeBoard(board)); // To insert every neighbor in the preority queue, but need to be a board pointer.

            //CODIGO PARA DEPURAR TODO: BORRAR DEPUES DE DEPURAR ejecutar esta parte
            vecino++;
            cout << "Vecino " << vecino << endl;
            cout << prueba[i].toString() << endl;
            cout << "P " << board->toString() << endl;
            cout << "ham: " << prueba[i].hamming() << endl;
            cout << "man: " << prueba[i].manhattan() << endl;
            cout << "********************";
            board = nullptr;
        }
    
        //for (Board nei : node.getBoard()->neighbors())
        //{
        //    board = &nei; //------------>This is in order to avoid modifying the neighbor method because that method returns a board, not a board pointer.
        //    priorityPQ->push(NodeBoard(board)); // To insert every neighbor in the preority queue, but need to be a board pointer.

        //    //CODIGO PARA DEPURAR TODO: BORRAR DEPUES DE DEPURAR
        //    vecino++;
        //    cout << "Vecino "<<vecino<<endl;
        //    cout << nei.toString() << endl;
        //    cout << "P "<<board->toString() << endl;
        //    cout << "ham: "<<nei.hamming() << endl;
        //    cout << "man: "<<nei.manhattan() << endl;
        //    cout << "********************";
        //    board = nullptr;
        //}

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

    } while (!node.getBoard()->isGoal());

    solvable = true;
    //TODO: DEPURAR PARA VER SI FUNICIONA.




}
