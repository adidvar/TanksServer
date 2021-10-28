#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "shapes.h"
#include "mvector.h"
#include "objectinterface.h"

class Object
{
protected:
    ObjectInterface &interface;

    Vector position;
    Vector size;
    float rotate;
    const bool active; //< визначає чи обєкт буде отримувати колізію
private:
    bool is_live = true;

public:
    Object (ObjectInterface &interface , Vector position , Vector size , float rotate , bool active);

    virtual MultiPointShape Poligon() const;
    virtual float Radius() const;
    friend bool ExecuteCollision(Object *obj1 , Object *obj2);

    virtual void Update(unsigned delta_time);
    bool IsValid();
    void Suicide();

    virtual void CollisionCycleBegin(unsigned delta_time) = 0;
    virtual void CollisionCycleEnd(unsigned delta_time) = 0;
    virtual void CollisionEvent(Object *obj , Vector normal , unsigned delta_time) = 0;

    bool Active();
};

#endif
