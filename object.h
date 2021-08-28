#ifndef RECT_H
#define RECT_H

#include <vector>
#include "math_tools/collision.h"
#include "math_tools/mvector.h"
#include "objectinterface.h"

class ObjectInterface;

class Object
{
protected:

    ObjectInterface *interface;

    Vector position;
    Vector size;
    float rotate;

protected:

    virtual MultiPointShape Poligon() const;
    virtual float Radius() const;

public:
    Object (ObjectInterface *interface , Vector position , Vector size , float rotate);

    virtual void Update();

    [[deprecated]]
    virtual void Collision(Object *obj , Vector normal);
    virtual void CollisionEnter(Object *obj , Vector normal);
    virtual void CollisionExit(Object *obj);
};

inline Object::Object(ObjectInterface *interface, Vector position, Vector size, float rotate):
    interface(interface),
    position(position),
    size(size),
    rotate(rotate)
{

}

#endif // RECT_H
