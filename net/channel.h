#ifndef CHANNEL_H
#define CHANNEL_H
#include <SFML/Network/TcpSocket.hpp>
#include <memory>

class channel;

struct disconnect_error
{
    channel *channel;
};
/**
 * @brief Абстрактний канал зв'язку
 */
class channel
{
    friend class Server;
    sf::TcpSocket sock;
public:
    channel();
    ~channel();
    void send(const void *data, std::size_t size);
    bool read(void *data, std::size_t size , size_t &read);
};

#endif // CHANNEL_H
