#ifndef MODULE_H
#define MODULE_H

#include <any>

#include "moduleinterface.h"

class Module
{
protected:
    ModuleInterface &environment;
public:
    Module(ModuleInterface &init);
    virtual ~Module() {};
    virtual void Start() = 0;
    virtual void Event(std::any& event) {};
};


#endif // MODULE_H
