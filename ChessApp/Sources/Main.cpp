#include "Application/Application.h"

int main(int argc, char *argv[])
{
    // DEMO
    if (argc > 1)
    {
        ChessGame cg;
        ChessIA::countSubNodes(cg, 6, true);
    }
    // /////

    std::cout << "(Press h for help)\n";
    Application App(800, 800);
    App.run();

	return 0;
}
