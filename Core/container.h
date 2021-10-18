#ifndef CONTAINER_H
#define CONTAINER_H

#include <list>
#include <memory>
#include <chrono>

#include "object.h"
#include "collision_visualizer.h"

class Container
{

#ifdef SCREEN
    collision_visualizer* visual;
#endif
    std::list<std::shared_ptr<Object>> objects;
public:
    Container();
    void Push(std::shared_ptr<Object> object);
    void Remove(std::shared_ptr<Object> obj);
    void Update();
};

#endif // CONTAINER_H
