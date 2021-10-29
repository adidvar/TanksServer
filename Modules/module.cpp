#include "module.h"
#include <iostream>

Module::Module(ModuleInterface &init):
    environment(init)
{

}

std::string Module::ModuleName() const
{
    return typeid(*this).name();
}
