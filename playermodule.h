#ifndef PLAYERMODULE_H
#define PLAYERMODULE_H

#include <memory>
#include <vector>

#include <boost/asio/deadline_timer.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

#include "module.h"
#include "net/player_controller.h"
#include "map.h"
#include "bulletmodule.h"
#include "debug_tools/out.h"
#include "net/archive.h"

using boost::asio::ip::tcp;

class PlayerModule : public Module
{
    std::vector<std::shared_ptr<player_controller>> players; ///< контролери
    boost::asio::deadline_timer update_timer;
    boost::asio::ip::tcp::acceptor acceptor;
    std::unique_ptr<tcp::socket> socket;
    std::shared_ptr<Map> map;
    std::shared_ptr<BulletModule> bullets;

public:
    PlayerModule(ModuleInterface &interface);

    using Player = player_controller;

    virtual void Start() override;
private:
    void Update(const boost::system::error_code&);
    void Accept(const boost::system::error_code&error);
};

#endif // PLAYERMODULE_H
