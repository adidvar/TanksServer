#ifndef OBJECT_H
#define OBJECT_H

#include "shapes.h"
#include "mvector.h"
#include "objectinterface.h"

class Object
{
protected:
    ObjectInterface &interface;

    const bool active; //< визначає чи обєкт буде отримувати колізію
private:
    bool is_live = true;

public:
    Object (ObjectInterface &interface , bool active);

    virtual MultiPointShape Poligon() const = 0;
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
