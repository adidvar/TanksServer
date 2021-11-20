#include "game.h"
#include "out.h"

#include "player_controller.h"
#include "map.h"
#include "bulletmodule.h"
#include "beaconmodule.h"
#include "texturesmodule.h"

#include <fstream>
#include <filesystem>

const std::chrono::milliseconds delay{10};

Game::Game(boost::asio::io_service &serv):
    interface(serv , modules , boost::bind(&Game::Event, this, boost::placeholders::_1)),
    update_timer(serv,std::chrono::milliseconds(delay))
{
    modules.emplace_back(new PlayerModule(interface));
    modules.emplace_back(new Map(interface,"map.json"));
    modules.emplace_back(new BeaconModule(interface));
//    modules.emplace_back(new TexturesModule(interface));
    modules.emplace_back(new BulletModule(interface));

    std::ifstream file("config.json");
    long long int length = filesystem::file_size("config.json");
    char * buffer = nullptr;

    boost::json::value root_v;
    try{
        buffer = new char[length];
        file.read(buffer, length);
        root_v = boost::json::parse( std::string(buffer, length) );
    } catch (std::bad_alloc &alloc) {
        root_v = boost::json::object();
    } catch (boost::system::system_error &error){
        cout << error.what() << endl;
        root_v = boost::json::object();
    }

    file.close();

    boost::json::object &root = root_v.as_object();

    delete[] buffer;

    for(auto &x :modules)
    {
        try {
            x->LoadSettings(root[x->ModuleName()].as_object());
        }  catch (std::invalid_argument &argument) {
            root[x->ModuleName()] = x->DefaultSettings();
            x->LoadSettings(root[x->ModuleName()].as_object());
        }
    }

    auto text = boost::json::serialize(root_v);
    ofstream ofile("config.json",ios_base::ate);
    ofile.write(text.data(),text.size());
    ofile.close();

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
    auto s_timer = std::chrono::steady_clock::now();
    interface.container.Update(std::chrono::duration_cast<std::chrono::milliseconds>(dur).count());
    auto uduration = std::chrono::steady_clock::now() - s_timer;

    update_timer.expires_from_now(delay);
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
