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

    virtual void CollisionCycleBegin(unsigned delta_time);
    virtual void CollisionCycleEnd(unsigned delta_time);
    virtual void CollisionEvent(Object *obj , Vector normal , unsigned delta_time);

    virtual MultiPointShape Poligon() const override;
};

#endif

