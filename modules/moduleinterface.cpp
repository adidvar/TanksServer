#include "moduleinterface.h"

ModuleInterface::ModuleInterface(boost::asio::io_service &serv, std::function<void (std::any)> sendevent):
    service(serv),
    sendevent(sendevent)
{

}

void ModuleInterface::SendEvent(std::any event)
{
    assert(this->sendevent);
    assert(event.has_value());
    sendevent(event);
}

ObjectInterface& ModuleInterface::ObjectInterface()
{
    return interface;
}

Container &ModuleInterface::Physics()
{
    return container;
}

boost::asio::io_service &ModuleInterface::Service()
{
    return service;
}
