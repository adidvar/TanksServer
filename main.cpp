#include <iostream>
#include <chrono>
#include "game.h"

using namespace std;

int main()
{
    boost::asio::io_service service;
    Game game(service);
    game.Run();
    return 0;
}
