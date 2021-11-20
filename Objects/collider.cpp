#include "collider.h"

Collider::Collider(ObjectInterface &obj, PointShape p):
    Object(obj, false)
{
    shape.shapes.emplace_back(std::move(p));
}

void Collider::CollisionCycleBegin(unsigned delta_time)
{

}

void Collider::CollisionCycleEnd(unsigned delta_time)
{

}

void Collider::CollisionEvent(Object *obj, Vector normal, unsigned delta_time)
{
}

MultiPointShape Collider::Poligon() const
{
    return shape;
}
