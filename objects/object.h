#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "../math/shapes.h"
#include "../math/mvector.h"
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

    virtual void Update();
    bool IsValid();
    void Suicide();

    [[deprecated]]
    virtual void Collision(Object *obj , Vector normal);
    virtual void CollisionEnter(Object *obj , Vector normal);
    virtual void CollisionExit(Object *obj);
    bool Active();
};

inline void Object::Suicide()
{
    this->is_live = false;
}

inline Object::Object(ObjectInterface &interface, Vector position, Vector size, float rotate, bool active):
    interface(interface),
    position(position),
    size(size),
    rotate(rotate),
    active(active)
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

inline float Object::Radius() const
{
    return 2.0f*static_cast<float>(sqrt(pow(size.x/2.0f,2.0) + pow(size.y/2.0f,2.0)));
}

inline void Object::Update()
{

}

inline bool Object::IsValid()
{
    return this->is_live;
}

inline void Object::Collision(Object *obj, Vector normal)
{

}

inline void Object::CollisionEnter(Object *obj, Vector normal)
{

}

inline void Object::CollisionExit(Object *obj)
{

}

inline bool Object::Active()
{
    return active;
}

#endif
