#include "game.h"
#include "debug_tools/out.h"

const unsigned delay = 10;

Game::Game():
    update_timer(interface.service,boost::posix_time::millisec(delay))
{
    interface.modules.emplace_back(new PlayerModule(interface));
    interface.modules.emplace_back(new Map(interface,"map.txt"));
    for(auto &x : interface.modules)
        x->Start();
    update_timer.async_wait(boost::bind(&Game::Update,this,boost::asio::placeholders::error));
}

void Game::Update(const boost::system::error_code &)
{
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

        interface.container.Update();

        { ///< Цикл магії пуль
         //   for(auto &i : this->bullets)
         //       i->Update();
/*
            auto it = find_if(bullets.begin(),bullets.end(),[](const auto &t1){return !t1->is_valid();});
            bullets.erase(it,bullets.end());
*/

        }

    update_timer.expires_from_now(boost::posix_time::millisec(delay));
    update_timer.async_wait(boost::bind(&Game::Update,this,boost::asio::placeholders::error));
}

void Game::Run()
{
    this->interface.service.run();
}
