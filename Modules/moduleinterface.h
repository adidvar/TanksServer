#ifndef MODULE_INTERFACE
#define MODULE_INTERFACE

#include <any>
#include <functional>

#include <boost/asio.hpp>

#include "container.h"
#include "objectinterface.h"

class Module;

class ModuleInterface
{
private:
    ObjectInterface interface;
    Container container;

    boost::asio::io_service &service;
    std::vector<std::shared_ptr<Module>> &modules;

    std::function<void(std::any)> sendevent;
public:
    ModuleInterface(boost::asio::io_service &serv , std::vector<std::shared_ptr<Module>> &modules , std::function<void(std::any)> sendevent);
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

    void SendEvent(std::any event);

    ObjectInterface& GetObjectInterface();
    Container& Physics();
    boost::asio::io_service& Service();
};

#endif
