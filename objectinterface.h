#ifndef OBJECTINTERFACE_H
#define OBJECTINTERFACE_H

#include <string>
#include <functional>
#include "object.h"

class Object;

class ObjectInterface
{
    std::function<void(Object*)> destroy;
public:
    ObjectInterface(std::function<void(Object*)> destroy);
    void Destory(Object*);
//    void Notificate(Object* , std::string);
};

#endif // OBJECTINTERFACE_H
