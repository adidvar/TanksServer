#ifndef MODULE_H
#define MODULE_H

#include <any>

#include <boost/json.hpp>

#include "moduleinterface.h"

class Module
{
protected:
    ModuleInterface &environment;
public:
    Module(ModuleInterface &init);
    virtual ~Module() {};

    virtual std::string ModuleName() const;
    virtual boost::json::object DefaultSettings() const = 0;
    virtual void LoadSettings(const boost::json::object &obj) = 0;

    virtual void Start() = 0;
    virtual void Event(std::any& event) {};
};


#endif // MODULE_H
