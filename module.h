#ifndef MODULE_H
#define MODULE_H
#include <boost/asio.hpp>
#include <functional>
#include <vector>
#include <memory>

#include "container.h"

class Module;

struct ModuleInterface
{
    ObjectInterface interface;
    boost::asio::io_service service;
    Container container;
    std::vector<std::shared_ptr<Module>> modules;

    template<typename ModuleType>
    std::shared_ptr<ModuleType> FindModule()
    {
        for (auto &i : modules)
        {
            if(dynamic_cast<ModuleType*>(i.get())!=nullptr)
                return std::dynamic_pointer_cast<ModuleType>(i);
        }
        return nullptr;
    };
};
//nclude <any>

enum struct Sourse 
{
    System = 0,
    Module = 1,
    Object = 2
};


class GameSignal
{
   Sourse from;
   std::any data;
public:
    GameSignal(Sourse from /*, std::any data*/) :
        from(from),
        data(data)
    {};
   Sourse From() { return from; }
   std::any Data() { return data; }
};

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
