#include "playermodule.h"

const unsigned delay = 10;

PlayerModule::PlayerModule(ModuleInterface &interface):
    Module(interface),
    update_timer(interface.service,boost::posix_time::millisec(delay))
{
}

void PlayerModule::Start()
{
    map = environment.FindModule<Map>();
    update_timer.async_wait(boost::bind(&PlayerModule::Update,this,boost::asio::placeholders::error));
}

void PlayerModule::Update(const boost::system::error_code &)
{
    {
        ///< Добавлення клієнтів в цикл
        auto client = host.Get();
        if(client != nullptr)
        {
            std::shared_ptr<player_controller> c(new player_controller(environment.interface,client,map));
            this->players.push_back(c);
            this->environment.container.Push(c->GetTank());
            info("New client");
        }
    }

    {   ///< Видалення закритих зєднаннь
        auto it = find_if(players.begin(),players.end(),[](const std::shared_ptr<player_controller> p){return !p->is_valid();});
        players.erase(it,players.end());
    }

    {  ///< Цикл відправлення таблиць
        std::vector<std::shared_ptr<Tank>> visible;
        for(const auto &i : this->players)
        {
            visible.push_back(i->GetTank());
        }

        for(auto &i : this->players)
        {
            i->update(visible);
//          i->update(bullets);
            i->events();
        }
    }

    update_timer.expires_from_now(boost::posix_time::millisec(delay));
    update_timer.async_wait(boost::bind(&PlayerModule::Update,this , boost::asio::placeholders::error));
}
