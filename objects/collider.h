#ifndef COLLIDER_H
#define COLLIDER_H

#include "object.h"

class Collider : public Object
{
protected:
    MultiPointShape shape;
    friend class Map;
public:
    Collider(ObjectInterface& obj, PointShape p);
    virtual void Collision(Object*, Vector) override;
    virtual MultiPointShape Poligon() const override;
};

#endif

