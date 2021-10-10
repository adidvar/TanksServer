#include <iostream>
#include "game.h"

using namespace std;

int main()
{
    Game *g = new Game();
    g->Run();
    delete g;
    return 0;
}
