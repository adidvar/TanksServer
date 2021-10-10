#ifndef CONTAINER_H
#define CONTAINER_H

#include <list>
#include <memory>

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
    void Push(const std::shared_ptr<Object> &obj);
    void Remove(std::shared_ptr<Object> obj);
    void Update();
};

#endif // CONTAINER_H
