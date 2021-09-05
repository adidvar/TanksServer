#ifndef SERVER_H
#define SERVER_H
#include <optional>
#include <SFML/Network/TcpListener.hpp>
#include "channel.h"

class Server;

#include "player_controller.h"

class Server
{
    sf::TcpListener listener;
    channel *chn;
public:
    Server();
    ~Server();

    channel *Get();
};

#endif // SERVER_H
