#include "map.h"

#include <filesystem>
#include <iostream>
#include <fstream>

#include "playermodule.h"

Map::Map(ModuleInterface &interface, std::string url):
    Module(interface)
{
   if( LoadMap(url) == false)
       std::cout << "Error while map loading" << std::endl;
}

boost::json::object Map::DefaultSettings() const
{
    boost::json::object set;
    return set;
}

void Map::LoadSettings(const boost::json::object &obj)
{

}

bool Map::LoadMap(std::string file_name)
{
    std::ifstream file(file_name , std::ios_base::binary);
    if(file.is_open()==false)
        return false;

    std::string map;
    std::vector<std::shared_ptr<Collider>> walls;
    std::vector<std::tuple<float , float , int>> spawns;

    auto size = std::filesystem::file_size(file_name);
    auto buffer = new char[size];
    file.read(buffer, size);
    map = std::string(buffer, size);
    delete[] buffer;
    file.close();

    try{
        boost::json::value root_value = boost::json::parse(map);
        boost::json::object &root = root_value.as_object();
        boost::json::array &colliders = root["collider"].as_array();
        boost::json::array &spawn_points = root["spawn points"].as_array();

        for(auto &col : colliders){
            auto &points = col.as_object()["points"].as_array();
            PointShape shape;
            for(auto &p : points){
                auto &pos = p.as_array();
                shape.points.emplace_back(Vector{static_cast<float>(pos[0].as_double()),static_cast<float>(pos[1].as_double())});
            }
            shape.convexity = col.as_object()["convexity"].as_bool();
            walls.emplace_back(new Collider(environment.GetObjectInterface(),shape));
        }

        for(boost::json::value &p_value : spawn_points){
            boost::json::object &point = p_value.as_object();
            spawns.push_back({point["x"].as_double() , point["y"].as_double() , point["team"].as_int64()});
        }
    }catch(bool){}/*catch (std::invalid_argument &argument){
        std::cout << argument.what() << std::endl;
        return false;
    }*/
    this->maptext = std::move(map);
    maptext.push_back('\n');
    this->spawn_points = std::move(spawns);
    this->walls = std::move(walls);
    return true;
}

void Map::Start()
{
    for( auto &x : this->walls)
        environment.Physics().Push(x);
    this->environment.SendEvent(MapUpdateEvent{this});
}

void Map::Event(std::any &sign)
{
    NewPlayerEvent *new_p = std::any_cast<NewPlayerEvent>(&sign);
    if (new_p != nullptr)
    {
        new_p->player->send(this->maptext);
    }
}

const std::vector<std::tuple<float, float, int> > &Map::GetSpawns() const
{
    return spawn_points;
}

const std::vector<std::shared_ptr<Collider> > &Map::GetWalls() const
{
    return walls;
}
