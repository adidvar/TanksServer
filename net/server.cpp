#include "server.h"

Server::Server()
{
    listener.listen(33334);
    listener.setBlocking(false);
    chn = new channel;
}

Server::~Server()
{
    listener.close();
}

std::optional<player_controller *> Server::Get()
{
    if( listener.accept(chn->sock) == sf::Socket::Done)
    {
        chn->sock.setBlocking(false);
        player_controller* player_cnt = new player_controller(chn);
        chn = new channel;
        return player_cnt;
    }
    return {};
}
