#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>
#include <memory>

#include "../objects/object.h"
#include "../collisions/collision_visualizer.h"

class Container
{

#ifdef SCREEN
    collision_visualizer visual;
#endif
    std::vector<std::shared_ptr<Object>> objects;
public:
    Container();
    void Push(std::shared_ptr<Object> obj);
    void Remove(std::shared_ptr<Object> obj);
    void Update();
};

#endif // CONTAINER_H
