#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include <memory>

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

#include <boost/json.hpp>

#include <tank.h>

using boost::asio::ip::tcp;

const size_t buffer_size = 1024;

class player_controller
{
    std::unique_ptr<tcp::socket> channel;
    std::shared_ptr<Tank> tank;
    bool valid = true;
    void destroy();
    char buffer[buffer_size];

    void readyread(const boost::system::error_code &code , size_t bytes_transfered); ///< обробка того що прийшло від клієнта
public:
    player_controller(ObjectInterface &interface, tcp::socket*);
    ~player_controller();

    boost::json::object GetPlayerJson() const;

    void send(std::string data);

    bool is_valid(){return valid;}
    std::shared_ptr<Tank> GetTank() const {return tank;};
};

#endif // PLAYER_CONTROLLER_H
