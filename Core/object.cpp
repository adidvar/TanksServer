#include "object.h"

Object::Object(ObjectInterface &interface, bool active):
    interface(interface),
    active(active)
{

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
