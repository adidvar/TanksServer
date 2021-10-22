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

    [[deprecated]]
    virtual void Collision(Object *obj , Vector normal);

    virtual void CollisionCycleBegin();
    virtual void CollisionCycleEnd();
    virtual void CollisionEvent(Object *obj , Vector normal);

    bool Active();
};

#endif
