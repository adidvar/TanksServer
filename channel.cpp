#include "channel.h"
#include "out.h"

channel::channel()
{
}

channel::~channel()
{
    sock.disconnect();
}

void channel::send(const void *data, std::size_t size)
{
    size_t sent;
    auto status = sock.send(data,size,sent);
    switch (status) {

    case sf::Socket::Disconnected:
        throw disconnect_error{this};
        break;

    case sf::Socket::Error:
        throw std::runtime_error("socket read error");
        break;

    default:

        break;
    }
    if(sent!=size)
        warning("warning sended only " + std::to_string(sent) + " of " + std::to_string(size));

}

bool channel::read(void *data, std::size_t size , size_t & read)
{
    auto status = sock.send(data,size,read);
    switch (status) {
    case sf::Socket::Done:
        return true;
        break;
    case sf::Socket::NotReady:
        return false;
        break;
    case sf::Socket::Partial:
        return false;
        break;
    case sf::Socket::Disconnected:
        throw disconnect_error{this};
        break;
    case sf::Socket::Error:
        throw std::runtime_error("socket read error");
        break;
    }
}
