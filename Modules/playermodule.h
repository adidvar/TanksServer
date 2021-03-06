#ifndef PLAYERMODULE_H
#define PLAYERMODULE_H

#include <memory>
#include <vector>
#include <chrono>
#include <unordered_map>

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

    boost::asio::steady_timer update_timer;
    boost::asio::ip::tcp::acceptor acceptor;
public:
    PlayerModule(ModuleInterface &interface);
    ~PlayerModule();

    virtual boost::json::object DefaultSettings() const override ;
    virtual void LoadSettings(const boost::json::object &obj) override;

    virtual void Start() override;
    void BroadCast(std::string text);
private:
    boost::json::object GenerateJson(const std::shared_ptr<player_controller>&current_user);
    void Update(const boost::system::error_code&);
    void Accept(tcp::socket* socket ,const boost::system::error_code&error);

    virtual void Event(std::any &event) override;
};

struct BroadCastEvent{
    std::string message;
};

struct NewPlayerEvent{
    std::shared_ptr<player_controller> player;
};

struct PlayerDisconnect{
    std::shared_ptr<player_controller> player;
};

#endif // PLAYERMODULE_H
