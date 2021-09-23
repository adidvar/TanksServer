#include "map.h"
#include "debug_tools/out.h"

#include <fstream>

Map::Map(ModuleInterface &interface, std::string url):
    Module(interface)
{
    std::fstream file;
    file.open(url);
    if(file.is_open()==false)
        error("cant open map.txt");

    info("Map loading...");

    Decor current(interface.interface);
    size_t back_c , walls_c;
    file >> back_c;
    for(size_t i = 0 ; i < back_c ; i++)
    {
        file >> current.position.x >> current.position.y >> current.size.x >> current.size.y >> current.rotate >> current.texture;

        if(!file)
        {
            error("MAP BACKGROUND ERROR");
        }

        backgrounds.push_back(current);
    }
    file >> walls_c;
    for(size_t i = 0 ; i < walls_c ; i++)
    {
        file >> current.position.x >> current.position.y >> current.size.x >> current.size.y >> current.rotate >> current.texture;
        if(!file)
        {
            error("MAP FOREGROUND ERROR");
        }
        walls.push_back(std::shared_ptr<Decor>(new Decor(current)));
    }
    file.close();

    info(std::string("Background items ") + to_string(this->backgrounds.size()));
    info(std::string("Foreground items ") + to_string(this->walls.size()));



}

void Map::Start()
{
    for( auto &x : this->walls)
        environment.container.Push(x);
}

void Map::write(archive &a)
{
    a.write("map_background");
    a.write(backgrounds.size());
    a.write(6);
    for(const auto &i : backgrounds)
    {
        a.write(i.position.x);
        a.write(i.position.y);
        a.write(i.size.x);
        a.write(i.size.y);
        a.write(i.rotate);
        a.write(i.texture);
    }
    a.packend();
    a.write("map_walls");
    a.write(walls.size());
    a.write(6);
    for(const auto &i : walls)
    {
        a.write(i->position.x);
        a.write(i->position.y);
        a.write(i->size.x);
        a.write(i->size.y);
        a.write(i->rotate);
        a.write(i->texture);
    }
    a.packend();
}

Decor::Decor(ObjectInterface &interface):
    Object(interface , {0,0} , {0,0} , 0 , false)
{

}

Decor::Decor(ObjectInterface &interface, Vector position, Vector size, float rotation):
    Object(interface , position , size , rotation , false)
{

}
