#include "map.h"
#include <out.h>
#include "player_controller.h"

#include <fstream>

Map::Map(ModuleInterface &interface, std::string url):
    Module(interface)
{
    std::fstream file;
    file.open(url);
    if(file.is_open()==false)
        error("cant open map.txt");

    info("Map loading...");
 
    size_t collider_count;
    file >> collider_count;
    for(size_t i = 0 ; i < collider_count ; i++)
    {
        PointShape shape;
        size_t point_counter;
        file >> point_counter;
        for (size_t j = 0; j < point_counter; j++)
        {
            float x, y;
            file >> x >> y;
            shape.points.emplace_back( x,y );
        }
        file >> shape.convexity;
        walls.emplace_back(new Collider(environment.ObjectInterface() , shape));
        environment.Physics().Push( dynamic_pointer_cast<Object>(walls.back()));
    }

    file.seekg(0, std::ios::end); 
    size_t length = file.tellg();    
    file.seekg(0, std::ios::beg);   
    char * buffer = new char[length];   
    file.read(buffer, length);  
    info(std::string("Length ") + to_string(length));
    maptext = std::string(buffer, length);
    delete[] buffer;

    file.close();

    info(std::string("Items ") + to_string(this->walls.size()));
    return ;
}

void Map::Start()
{
    for( auto &x : this->walls)
        environment.Physics().Push(x);
}

void Map::Signal(GameSignal sign)
{
    std::shared_ptr<player_controller>* controller;
    controller = std::any_cast<std::shared_ptr<player_controller>>(&sign);
    if (controller != nullptr) 
    {
        archive a;
        a.write("Map");
        a.write(maptext);
        a.packend();
        (*controller)->send(a.text());
    }
}
