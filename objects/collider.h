#ifndef COLLIDER_H
#define COLLIDER_H

#include "object.h"

class Collider : public Object
{
protected:
    MultiPointShape shape;
    friend class Map;
public:
    Collider(ObjectInterface &);
    Collider(ObjectInterface& obj, PointShape p):
        Object(obj, { 0,0 }, { 0,0 } , 0 , false)
    {
        shape.shapes.emplace_back(std::move(p));
    }
    virtual void Collision(Object*, Vector) override
    {
    }
    virtual MultiPointShape Poligon() const override
    {
        return shape;
    }
};

#endif

