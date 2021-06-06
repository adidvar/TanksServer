#ifndef GAME_MAP_H
#define GAME_MAP_H
#include <vector>
#include <string>

#include "net/archive.h"
#include "math_tools/rect.h"


struct map_rect : public rect
{
    std::string texture;
    template<typename T>
    void Collision(T, Vector2f){};
};

class Map
{
public:
    std::vector<map_rect> back_data;
    std::vector<map_rect> wall_data;
public:
    Map(std::string url);


    void write(archive &arc);
};

#endif // GAME_MAP_H
