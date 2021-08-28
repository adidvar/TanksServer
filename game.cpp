#include "game.h"
#include "debug_tools/out.h"
#include <thread>
#include <time.h>

void game::loop()
{
    while(true)
    {
        size_t begin_timer= clock();


        {	///< Добавлення клієнтів в цикл
            auto client = host.Get();
            if(client.has_value())
            {
                shared_ptr<Tank> _tank (new Tank([this](Bullet*bullet){this->bullets.emplace_back(bullet);}));
                shared_ptr<player_controller> c(client.value());
                c->start(_tank,this);
                this->players.insert({c,_tank});
                info("New client");
            }
        }

        {   ///< Видалення закритих зєднаннь
            auto it = find_if(players.begin(),players.end(),[](const auto &t1){return !t1.first->is_valid();});
            players.erase(it,players.end());
        }


#ifdef SCREEN
        {
            visual.lock();
            visual.clear();
            for(const auto &x : this->_map.wall_data)
                visual.push(x.Split());
            for(auto x : this->bullets)
                visual.push(x->Split());
            for(auto x : this->players)
                visual.push(x.second->Split());


            visual.unlock();
        }
#endif

        {   ///< Цикл колізій

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


        }

        {  ///< Цикл відправлення таблиць

            std::vector<shared_ptr<Tank>> visible;
            for(const auto &i : this->players)
            {
                if(i.second->islive())
                    visible.push_back(i.second);
            }

            for(auto &i : this->players)
            {
                i.first->update(visible);
                i.first->update(bullets);
                i.first->events();
                i.second->update(1);
            }

        }

        { ///< Цикл магії пуль
            for(auto &i : this->bullets)
                i->Update(1);

            auto it = find_if(bullets.begin(),bullets.end(),[](const auto &t1){return !t1->is_valid();});
            bullets.erase(it,bullets.end());


        }

        size_t end_timer=clock();

        this_thread::sleep_for(chrono::milliseconds(10));
    }
}
