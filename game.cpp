#include "game.h"
#include "debug_tools/out.h"
#include <thread>
#include <time.h>

game::game():
    map("map.txt" , container)
{
}

void game::loop()
{
    while(true)
    {
        size_t begin_timer= clock();


        {	///< Добавлення клієнтів в цикл
            auto client = host.Get();
            if(client != nullptr)
            {
                shared_ptr<player_controller> c(new player_controller(client,this));
                this->players.push_back(c);
                container.Push(c->GetTank());
                info("New client");
            }
        }

        {   ///< Видалення закритих зєднаннь
            auto it = find_if(players.begin(),players.end(),[](const shared_ptr<player_controller> p){return !p->is_valid();});
            players.erase(it,players.end());
        }

        {   ///< Цикл колізій
/*
            for(map_rect& x : this->_map.wall_data)
                for(const auto &tank : this->players)
                    collision(&x,tank.second);

            for(const auto &tank1 : this->players)
                for(const auto &tank : this->players)
                    if(tank1!=tank)
                        collision(tank1.second,tank.second);

            for(const auto &tank : this->players)
                for(const Bullet::Ptr &bullet : this->bullets)
                      collision(bullet,tank.second);

*/
        }

        {  ///< Цикл відправлення таблиць
            std::vector<shared_ptr<Tank>> visible;
            for(const auto &i : this->players)
            {
                visible.push_back(i->GetTank());
            }

            for(auto &i : this->players)
            {
                i->update(visible);
                i->update(bullets);
                i->events();
            }
        }
        container.Update();

        { ///< Цикл магії пуль
            for(auto &i : this->bullets)
                i->Update();
/*
            auto it = find_if(bullets.begin(),bullets.end(),[](const auto &t1){return !t1->is_valid();});
            bullets.erase(it,bullets.end());
*/

        }

        size_t end_timer=clock();

        this_thread::sleep_for(chrono::milliseconds(10));
    }
}
