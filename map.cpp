#include "map.h"
#include "debug_tools/out.h"

#include <fstream>

Map::Map(std::string url, Container &container):
    container(container)
{
    std::fstream file;
    file.open(url);
    if(file.is_open()==false)
        error("cant open map.txt");

    Decor current;
    size_t back_c , walls_c;
    file >> back_c;
    for(size_t i = 0 ; i < back_c ; i++)
    {
        file >> current.position.x >> current.position.y >> current.size.x >> current.size.y >> current.rotate >> current.texture;

        if(!file)
        {
            cout << "map ... error \n";
            exit(1);
        }

        backgrounds.push_back(current);
    }
    file >> walls_c;
    for(size_t i = 0 ; i < walls_c ; i++)
    {
        file >> current.position.x >> current.position.y >> current.size.x >> current.size.y >> current.rotate >> current.texture;
        if(!file)
        {
            cout << "map ... error \n";
            exit(1);
        }
        walls.push_back(std::shared_ptr<Decor>(new Decor(current)));
    }
    file.close();

    for( auto &x : this->walls)
        container.Push(x);


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
}

Decor::Decor():
    Object(nullptr , {0,0} , {0,0} , 0 , false)
{

}

Decor::Decor(Vector position, Vector size, float rotation):
    Object(nullptr , position , size , rotation , false)
{

}
