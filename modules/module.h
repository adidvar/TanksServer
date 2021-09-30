#ifndef MODULE_H
#define MODULE_H

#include <boost/asio.hpp>
#include <vector>
#include <memory>
#include <queue>

#include "container.h"
#include "gamesignal.h"

class Module;

class ModuleInterface
{
private:

    boost::asio::io_service service;

    ObjectInterface interface;
    Container container;

    std::vector<std::shared_ptr<Module>> modules;
    std::queue<GameSignal> signals;
public:
    ModuleInterface() {};
    
    friend class Game;

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

    void EmitSignal(GameSignal signal)
    {
        signals.push(signal);
    }

    Container& Physics()
    {
        return container;
    }

    boost::asio::io_service& Service()
    {
        return service;
    }

    ObjectInterface& ObjInterface()
    {
        return interface;
    }
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
