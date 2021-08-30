#ifndef RECT_H
#define RECT_H

#include <vector>
#include "math_tools/shapes.h"
#include "math_tools/mvector.h"
#include "objectinterface.h"

class ObjectInterface;
class MultiPointShape;

class Object
{
protected:

    ObjectInterface *interface;

    Vector position;
    Vector size;
    float rotate;

public:
    Object (ObjectInterface *interface , Vector position , Vector size , float rotate);


    virtual MultiPointShape Poligon() const;
    virtual float Radius() const;
    friend void ExecuteCollision(Object *obj1 , Object *obj2);

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

inline MultiPointShape Object::Poligon() const
{
    auto shape = PointShape{
        {
        {size.x/2.0f , size.y/2.0f},
        {size.x/2.0f , -size.y/2.0f},
        {-size.x/2.0f , -size.y/2.0f},
        {-size.x/2.0f , size.y/2.0f}},
        true};
    for(size_t i = 0 ;i < 4 ; i++)
    {
        shape.points[i] = shape.points[i].Rotate(rotate);
        shape.points[i] = shape.points[i] + Vector{position.x,position.y};
    }
    return MultiPointShape{std::vector{shape}};
}

#endif // RECT_H
