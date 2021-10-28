#ifndef CONTAINER_H
#define CONTAINER_H

#include <list>
#include <memory>
#include <chrono>

#include "object.h"

class Container
{

#ifdef SCREEN
    collision_visualizer* visual;
#endif
    std::vector<std::shared_ptr<Object>> objects;
public:
    Container();
    void Push(std::shared_ptr<Object> object);
    void Remove(std::shared_ptr<Object> obj);
    void Update(unsigned delta_time);
};

#endif // CONTAINER_H
