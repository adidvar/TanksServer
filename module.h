#ifndef MODULE_H
#define MODULE_H
#include <boost/asio.hpp>
#include "container.h"
#include <functional>
#include <vector>
#include <memory>

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
    };
};

class Module
{
protected:
    ModuleInterface &environment;
public:
    Module(ModuleInterface &init);
    virtual void Start() = 0;
};

#endif // MODULE_H
