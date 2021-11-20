#include "moduleinterface.h"

ModuleInterface::ModuleInterface(boost::asio::io_service &serv, std::vector<std::shared_ptr<Module> > &modules, std::function<void (std::any)> sendevent):
    service(serv),
    modules(modules),
    sendevent(sendevent)
{

}

void ModuleInterface::SendEvent(std::any event)
{
    assert(this->sendevent);
    assert(event.has_value());
    sendevent(event);
}

ObjectInterface& ModuleInterface::GetObjectInterface()
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
