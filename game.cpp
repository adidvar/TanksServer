#include "game.h"
#include "out.h"
#include <thread>

void game::loop()
{
    while(true)
    {
        auto client = host.Get();
        if(client.has_value())
        {
            shared_ptr<tank> _tank (new tank());
            auto c = client.value();
            c->start(_tank,this);
            this->players[c] = _tank;
            info("New client");
        }

        auto it = find_if(players.begin(),players.end(),[](std::pair<player_controller* , shared_ptr<tank>> t1){return !t1.first->is_valid();});
        players.erase(it,players.end());

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
        this_thread::sleep_for(chrono::milliseconds(20));
        this_thread::yield();
    }
}
