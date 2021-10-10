#ifndef PLAYERMODULE_H
#define PLAYERMODULE_H

#include <memory>
#include <vector>

#include <boost/asio/deadline_timer.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <archive.h>

#include "module.h"
#include "player_controller.h"

using boost::asio::ip::tcp;

class PlayerModule : public Module
{
    std::vector<std::shared_ptr<player_controller>> players; ///< контролери

    boost::asio::deadline_timer update_timer;
    boost::asio::ip::tcp::acceptor acceptor;
    std::unique_ptr<tcp::socket> socket;

public:
    PlayerModule(ModuleInterface &interface);

    virtual void Start() override;
    void BroadCast(std::string text);
private:
    void Update(const boost::system::error_code&);
    void Accept(const boost::system::error_code&error);
};

#endif // PLAYERMODULE_H
