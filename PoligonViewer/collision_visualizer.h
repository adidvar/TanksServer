#ifndef COLLISION_VISUALIZER_H
#define COLLISION_VISUALIZER_H

//#define SCREEN

#ifdef SCREEN

#include <vector>
#include <thread>
#include <mutex>

#include "mvector.h"
#include "shapes.h"

class collision_visualizer
{
    std::thread th;

    std::vector<Line> lines;
    std::vector<Line> colisions;

    std::mutex l_mutex;

    void render();
public:
    collision_visualizer();
    void push(MultiPointShape lines);
    void pushCollision(MultiPointShape lines);
    void clear();
};

#endif // SCREEN


#endif // COLLISION_VISUALIZER_H
