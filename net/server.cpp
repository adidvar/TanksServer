#include "server.h"

Server::Server()
{
    listener.listen(33334);
    listener.setBlocking(false);
    chn = new channel;
    chn->sock.setBlocking(false);
}

Server::~Server()
{
    listener.close();
}

channel* Server::Get()
{
    if( listener.accept(chn->sock) == sf::Socket::Done)
    {
        auto chanel = chn;
        chn = new channel;
        chn->sock.setBlocking(false);

        return chanel;
    }
    return nullptr;
}
