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
        error("cant open map.txt");

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
        this->walls.emplace_back(new Collider(environment.ObjectInterface(),shape));
    }




    file.close();

    info(std::string("Items ") + to_string(this->walls.size()));
    return ;
}

void Map::Start()
{
    for( auto &x : this->walls)
        environment.Physics().Push(x);
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
