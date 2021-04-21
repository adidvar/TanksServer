#include <iostream>
#include "tank.h"
#include <game.h>
#include <SFML/Network.hpp>
#include <optional>
#include <tuple>
#include <string>

using namespace std;

int main()
{
    game g;

    sf::TcpListener listener;
    listener.listen(33334);
    listener.setBlocking(false);

    sf::TcpSocket *pending_socket = new sf::TcpSocket;

    while(1)
    {
       if( listener.accept(*pending_socket) == sf::Socket::Done)
       {
            pending_socket->setBlocking(false);
            g.enter(pending_socket);
            pending_socket = new sf::TcpSocket();

       }
       g.read_clinets();
       g.update_map(1.0);
       g.send_update();
    }
    return 0;
}
