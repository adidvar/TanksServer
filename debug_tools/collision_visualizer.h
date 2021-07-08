#ifndef COLLISION_VISUALIZER_H
#define COLLISION_VISUALIZER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include <mutex>

#include "math_tools/vector2f.h"
class collision_visualizer
{
    sf::RenderWindow* window;
    std::thread *th;
    std::vector<line> lines;
    std::mutex l_mutex;
public:
    collision_visualizer();
    void render();
    void push(std::vector<line> lines);
    void clear();
    void lock();
    void unlock();
};

#endif // COLLISION_VISUALIZER_H
