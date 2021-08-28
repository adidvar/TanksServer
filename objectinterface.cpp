#include "objectinterface.h"

ObjectInterface::ObjectInterface(std::function<void (Object *)> destroy):
    destroy(destroy)
{
}

void ObjectInterface::Destory(Object * pointer)
{
    destroy(pointer);
}
