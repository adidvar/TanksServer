#include "playermodule.h"
#include "map.h"

#include <out.h>

static std::chrono::milliseconds delay {10};

PlayerModule::PlayerModule(ModuleInterface &interface):
    Module(interface),
    update_timer(interface.Service(),delay),
    acceptor(interface.Service(), tcp::endpoint(tcp::v4(),33334))
{
}

PlayerModule::~PlayerModule()
{
    this->acceptor.cancel();
}

boost::json::object PlayerModule::DefaultSettings() const
{
   boost::json::object set;
   set["move_speed"] = 0.00125f;
   set["rotate_speed"] = 0.00125f;
   set["tower_speed"] = 0.00125f;
   set["delay"] = delay.count();
   return set;
}

void PlayerModule::LoadSettings(const boost::json::object &obj)
{
    boost::json::object copy = obj;
    Tank::move_speed = copy["move_speed"].as_double();
    Tank::rotation_speed = copy["rotate_speed"].as_double();
    Tank::tower_speed = copy["tower_speed"].as_double();
    delay = std::chrono::milliseconds(copy["delay"].as_uint64());
}

void PlayerModule::Start()
{
    tcp::socket *sock = new tcp::socket(environment.Service());
    acceptor.async_accept(*sock,boost::bind(&PlayerModule::Accept,this , sock ,boost::asio::placeholders::error));
    update_timer.async_wait(boost::bind(&PlayerModule::Update,this,boost::asio::placeholders::error));
}

void PlayerModule::Update(const boost::system::error_code &error)
{ 
    if(error){
        warning(error.message());
        return;
    }

    {   ///< Видалення закритих зєднаннь
        auto it = remove_if(players.begin(),players.end(),[](const std::shared_ptr<player_controller> p){return !p->is_valid();});

        for(auto it_b = it ; it_b != players.end() ; ++it_b)
            environment.SendEvent(PlayerDisconnect{*it_b});

        players.erase(it,players.end());
    }
    for(auto& user : this->players){
        auto tank = user->GetTank();
        if(tank->IsLive() == false)
        {
            auto[x , y , team] = spawns.at(rand()%spawns.size());
            tank->Spawn({x,y},tank->Team());
        }

    }
    for(const auto& user : this->players){
        auto package = boost::json::serialize(GenerateJson(user));
        package.push_back('\n');
        user->send(package);
    }

    update_timer.expires_at(std::chrono::steady_clock::now() + delay);
    update_timer.async_wait(boost::bind(&PlayerModule::Update,this , boost::asio::placeholders::error));
}

void PlayerModule::BroadCast(std::string text)
{
    for (auto& client : this->players)
        if(client->is_valid())
            client->send(text);
}

boost::json::object PlayerModule::GenerateJson(const std::shared_ptr<player_controller> &current_user)
{
    boost::json::object root;
    boost::json::array users;
    for(const auto &user : this->players)
        users.push_back(user->GetPlayerJson());
    root["type"] = "users";
    root["users"] = users;
    root["me"] = current_user->GetPlayerJson();
    return root;
}

void PlayerModule::Accept(tcp::socket* socket, const boost::system::error_code & error)
{
    if(error){
        warning(error.message());
        delete socket;
        return;
    }

    std::shared_ptr<player_controller> c(new player_controller(environment.GetObjectInterface(), socket));
    this->players.push_back(c);

    auto[x , y , team] = spawns.at(rand()%spawns.size());

    c->GetTank()->Spawn({ x,y }, rand());
    this->environment.Physics().Push(c->GetTank());
    this->environment.SendEvent(NewPlayerEvent{c});
    info("New client");

    tcp::socket *new_sock = new tcp::socket(environment.Service());
    acceptor.async_accept( *new_sock , boost::bind(&PlayerModule::Accept,this, new_sock , boost::asio::placeholders::error));
}

void PlayerModule::Event(std::any &event)
{
    BroadCastEvent *broadcast = std::any_cast<BroadCastEvent>(&event);
    if( broadcast != nullptr )
    {
        BroadCast(broadcast->message);
    }
    MapUpdateEvent *map_update = std::any_cast<MapUpdateEvent>(&event);
    if( map_update != nullptr){
        this->spawns = map_update->map->GetSpawns();
    }

}
