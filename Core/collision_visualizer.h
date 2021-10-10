#ifndef COLLISION_VISUALIZER_H
#define COLLISION_VISUALIZER_H

//#define SCREEN

#ifdef SCREEN

#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include <mutex>

#include "mvector.h"
#include "shapes.h"

class collision_visualizer
{
    sf::RenderWindow* window;
    std::thread *th;
    std::vector<Line> lines;
    std::vector<Line> colisions;
    std::mutex l_mutex;
public:
    collision_visualizer();
    void render();
    void push(MultiPointShape lines);
    void pushCollision(MultiPointShape lines);
    void clear();
    void lock();
    void unlock();
};

#endif // SCREEN


#endif // COLLISION_VISUALIZER_H
