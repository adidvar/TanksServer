#include "map.h"
#include <out.h>
#include "player_controller.h"

#include <assert.h>

#include <fstream>

Map::Map(ModuleInterface &interface, std::string url):
    Module(interface)
{
    std::fstream file;
    file.open(url);
    if(file.is_open()==false)
        error("Cant open map.json");

    info("Map loading...");

    file.seekg(0, std::ios::end); 
    size_t length = file.tellg();    
    file.seekg(0, std::ios::beg);   
    char * buffer = new char[length];   
    file.read(buffer, length);  
    info(std::string("Length ") + to_string(length));
    maptext = std::string(buffer, length);
    maptext.push_back('\n');
    delete[] buffer;

    boost::json::value root = boost::json::parse(maptext);

    boost::json::object &root_obj = root.as_object();
    boost::json::array &colliders = root_obj["collider"].as_array();
    for(auto &col : colliders){
        auto &points = col.as_object()["points"].as_array();
        PointShape shape;
        for(auto p : points){
            auto pos = p.as_array();
            shape.points.emplace_back(Vector{static_cast<float>(pos[0].as_double()),static_cast<float>(pos[1].as_double())});
        }
        shape.convexity = col.as_object()["convexity"].as_bool();
        this->walls.emplace_back(new Collider(environment.ObjectInterface(),shape));
    }
    info(std::string("Items ") + to_string(this->walls.size()));

    auto spawn_points = root_obj["spawn points"].as_array();
    for(auto p : spawn_points){
        auto p_obj = p.as_object();
        this->spawn_points.push_back({p_obj["x"].as_double() , p_obj["y"].as_double() , p_obj["team"].as_int64()});
    }
    info(std::string("Spawns ")+to_string(spawn_points.size()));

    file.close();

    return ;
}

void Map::Start()
{
    for( auto &x : this->walls)
        environment.Physics().Push(x);
    this->environment.SendEvent(MapUpdateEvent{this});
}

void Map::Event(std::any &sign)
{
    std::shared_ptr<player_controller>* controller;
    controller = std::any_cast<std::shared_ptr<player_controller>>(&sign);
    if (controller != nullptr) 
    {
        (*controller)->send(this->maptext);
    }
}

const std::vector<std::tuple<float, float, int> > &Map::GetSpawns()
{
    return this->spawn_points;
}
