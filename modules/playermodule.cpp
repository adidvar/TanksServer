#include "playermodule.h"
#include "../net/archive.h"
#include "../debug_tools/out.h"

const unsigned delay = 10;

PlayerModule::PlayerModule(ModuleInterface &interface):
    Module(interface),
    update_timer(interface.Service(),boost::posix_time::millisec(delay)),
    acceptor(interface.Service(), tcp::endpoint(tcp::v4(),33334))
{
}

void PlayerModule::Start()
{
    update_timer.async_wait(boost::bind(&PlayerModule::Update,this,boost::asio::placeholders::error));
    socket.reset(new tcp::socket(environment.Service()));
    acceptor.async_accept(*this->socket.get(),boost::bind(&PlayerModule::Accept,this ,boost::asio::placeholders::error));
}

void PlayerModule::Update(const boost::system::error_code &e)
{ 
    {   ///< Видалення закритих зєднаннь
        auto it = remove_if(players.begin(),players.end(),[](const std::shared_ptr<player_controller> p){return !p->is_valid();});
        players.erase(it,players.end());
    }

    {  ///< Цикл відправлення таблиць
        std::vector<std::shared_ptr<Tank>> visible;
        for(const auto &i : this->players)
            visible.push_back(i->GetTank());

        for(auto &i : this->players)
            i->update(visible);
    }

    update_timer.expires_from_now(boost::posix_time::millisec(delay));
    update_timer.async_wait(boost::bind(&PlayerModule::Update,this , boost::asio::placeholders::error));
}

void PlayerModule::BroadCast(std::string text)
{
    for (auto& client : this->players)
        if(client->is_valid())
          client->send(text);
}

void PlayerModule::Accept(const boost::system::error_code & error)
{
    if(!error)
    {
            std::shared_ptr<player_controller> c(new player_controller(environment.ObjInterface(),std::move(socket)));
            this->players.push_back(c);
            c->GetTank()->Spawn({ 0,0 }, rand());
            this->environment.Physics().Push(c->GetTank());
            info("New client");

            this->environment.EmitSignal(GameSignal(c));


            socket.reset(new tcp::socket(environment.Service()));
            acceptor.async_accept(*this->socket.get(),boost::bind(&PlayerModule::Accept,this , boost::asio::placeholders::error));
    }
}
