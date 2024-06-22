#include "Utils/Demo.h"

namespace Demo
{

    const DemoGame getDemoGame(int x)
    {
        switch (x)
        {
        case 1:
            return DemoGame(demoBoard1, demoPlayers1, 0);

        case 2:
            return DemoGame(demoBoard2, demoPlayers2, 0);

        default:
            return DemoGame(demoDefaultBoard, demoDefaultPlayers, 0);
        }
    }

}