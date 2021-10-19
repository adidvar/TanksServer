#include "game.h"
#include "out.h"

#include "player_controller.h"
#include "map.h"
#include "bulletmodule.h"

const unsigned delay = 10;

Game::Game(boost::asio::io_service &serv):
    interface(serv , boost::bind(&Game::Event, this, boost::placeholders::_1)),
    update_timer(serv,std::chrono::milliseconds(delay))
{
    modules.emplace_back(new PlayerModule(interface));
    modules.emplace_back(new Map(interface,"map.json"));
    modules.emplace_back(new BulletModule(interface));

    interface.interface.spawnbullet = std::bind(&BulletModule::SpawnBullet , dynamic_cast<BulletModule*>(modules.back().get()) , std::placeholders::_1);

    for(auto &x : modules)
        x->Start();

    update_timer.async_wait(boost::bind(&Game::Update,this,boost::asio::placeholders::error));
}

void Game::Update(const boost::system::error_code &error)
{
    if(error) {
        warning(error.message());
        return;
    }

    static auto timer = std::chrono::steady_clock::now();
    auto dur = std::chrono::steady_clock::now() - timer;
    timer = std::chrono::steady_clock::now();

    while(!events.empty())
    {
        std::any event = events.front();
        events.pop();
        for (auto& module : modules)
            module->Event(event);
    }

    interface.container.Update();

    cout << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << endl;


    update_timer.expires_from_now(std::chrono::milliseconds(delay));
    update_timer.async_wait(boost::bind(&Game::Update,this,boost::asio::placeholders::error));
}

void Game::Event(std::any event)
{
    this->events.push(event);
}


void Game::Run()
{
    this->interface.service.run();
}
