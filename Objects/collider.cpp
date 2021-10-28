#include "collider.h"

Collider::Collider(ObjectInterface &obj, PointShape p):
    Object(obj, { 0,0 }, { 0,0 } , 0 , false)
{
    shape.shapes.emplace_back(std::move(p));
}

void Collider::CollisionCycleBegin()
{

}

void Collider::CollisionCycleEnd()
{

}

void Collider::CollisionEvent(Object *obj, Vector normal)
{
}

MultiPointShape Collider::Poligon() const
{
    return shape;
}
