#ifndef PLAYERMODULE_H
#define PLAYERMODULE_H

#include <memory>
#include <vector>

#include <boost/asio/deadline_timer.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

#include "module.h"
#include "player_controller.h"

using boost::asio::ip::tcp;

class PlayerModule : public Module
{
    std::vector<std::shared_ptr<player_controller>> players; ///< контролери
    std::vector<std::tuple<float,float,int>> spawns;

    boost::asio::deadline_timer update_timer;
    boost::asio::ip::tcp::acceptor acceptor;
public:
    PlayerModule(ModuleInterface &interface);
    ~PlayerModule();

    virtual void Start() override;
    void BroadCast(std::string text);
private:
    boost::json::object GenerateJson(const std::shared_ptr<player_controller>&current_user);
    void Update(const boost::system::error_code&);
    void Accept(tcp::socket* socket ,const boost::system::error_code&error);

    virtual void Event(std::any &event) override;
};

#endif // PLAYERMODULE_H
