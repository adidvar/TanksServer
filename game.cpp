#include "game.h"
#include "debug_tools/out.h"
#include <thread>

void game::loop()
{
    while(true)
    {
        auto client = host.Get();
        if(client.has_value())
        {
            shared_ptr<tank> _tank (new tank());
            shared_ptr<player_controller> c(client.value());
            c->start(_tank,this);
            this->players.insert({c,_tank});
            info("New client");
        }

        auto it = find_if(players.begin(),players.end(),[](const auto &t1){return !t1.first->is_valid();});
        players.erase(it,players.end());


        for(map_rect& x : this->_map.wall_data)
            for(const auto &tank : this->players)
                collision(&x,tank.second);
        for(auto tank1 : this->players)
            for(const auto &tank : this->players)
                if(tank1!=tank)
                    collision(tank1.second,tank.second);


        std::vector<shared_ptr<tank>> visible;

        for(const auto &i : this->players)
        {
            if(i.second->islive())
                visible.push_back(i.second);
        }

        for(auto &i : this->players)
        {
            i.first->update(visible);
            i.first->events();
            i.second->update(1);
        }
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}
