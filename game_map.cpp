#include "game_map.h"
#include "debug_tools/out.h"

#include <fstream>

Map::Map(std::string url)
{
    std::fstream file;
    file.open(url);
    if(file.is_open()==false)
        error("cant open map.txt");

    map_rect current;
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

        back_data.push_back(current);
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
        wall_data.push_back(current);
    }
    file.close();
}

void Map::write(archive &a)
{
    a.write("map_background");
    a.write(back_data.size());
    a.write(6);
    for(const auto &i : back_data)
    {
        a.write(i.position.x);
        a.write(i.position.y);
        a.write(i.size.x);
        a.write(i.size.y);
        a.write(i.rotate);
        a.write(i.texture);
    }
    a.write("map_walls");
    a.write(wall_data.size());
    a.write(6);
    for(const auto &i : wall_data)
    {
        a.write(i.position.x);
        a.write(i.position.y);
        a.write(i.size.x);
        a.write(i.size.y);
        a.write(i.rotate);
        a.write(i.texture);
    }
}

