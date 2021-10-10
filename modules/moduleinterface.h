#ifndef MODULE_INTERFACE
#define MODULE_INTERFACE

#include <boost/asio.hpp>

#include "container.h"
#include "objectinterface.h"
#include <gamesignal.h>

#include <vector>
#include <memory>
#include <queue>

class Module;

class ModuleInterface
{
private:
    ObjectInterface interface;
    boost::asio::io_service service;
    Container container;
    std::vector<std::shared_ptr<Module>> modules;
    std::queue<GameSignal> signals;
public:
    ModuleInterface() = default;
    
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

    ObjectInterface& ObjectInterface()
    {
        return interface;
    }

    Container& Physics()
    {
        return container;
    }

    boost::asio::io_service& Service()
    {
        return service;
    }
};

#endif
