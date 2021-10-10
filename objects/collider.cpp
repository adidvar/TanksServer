#include "collider.h"

Collider::Collider(ObjectInterface &obj, PointShape p):
    Object(obj, { 0,0 }, { 0,0 } , 0 , false)
{
    shape.shapes.emplace_back(std::move(p));
}

void Collider::Collision(Object *, Vector)
{
}

MultiPointShape Collider::Poligon() const
{
    return shape;
}
