#ifndef MODULE_H
#define MODULE_H

#include "moduleinterface.h"
#include "gamesignal.h"

class Module
{
protected:
    ModuleInterface &environment;
public:
    Module(ModuleInterface &init);
    virtual void Start() = 0;
    virtual void Signal(GameSignal sign) {};
};


#endif // MODULE_H
