#include "object.h"

Object::Object(ObjectInterface &interface, Vector position, Vector size, float rotate, bool active):
    interface(interface),
    position(position),
    size(size),
    rotate(rotate),
    active(active)
{

}

MultiPointShape Object::Poligon() const
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

float Object::Radius() const
{
    return 2.0f*static_cast<float>(sqrt(pow(size.x/2.0f,2.0) + pow(size.y/2.0f,2.0)));
}

void Object::Update(unsigned delta_time)
{

}

void Object::Suicide()
{
    this->is_live = false;
}

bool Object::IsValid()
{
    return this->is_live;
}

bool Object::Active()
{
    return active;
}
