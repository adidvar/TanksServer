#include <iostream>
#include <chrono>
#include "game.h"

#ifdef _WIN32
#include <timeapi.h>
#endif

using namespace std;

int main()
{

#ifdef _WIN32
    timeBeginPeriod(1);
#endif

    boost::asio::io_service service;
    Game game(service);
    game.Run();
    return 0;
}
