#ifndef BEACONMODULE_H
#define BEACONMODULE_H

#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <boost/bind/bind.hpp>

#include "module.h"
#include "playermodule.h"


class BeaconModule : public Module
{
    boost::asio::ip::udp::socket acceptor;
public:
    BeaconModule(ModuleInterface &interface);
    virtual ~BeaconModule() override;
    virtual void Start() override {};
private:
    boost::json::object GenerateJson();
    void ReadyRead(const boost::system::error_code &error , size_t transfered);

    virtual void Event(std::any &event) override {};

    const static size_t buffer_size = 1024;
    int8_t buffer[buffer_size];
    boost::asio::ip::udp::endpoint endpoint;
};

#endif // PLAYERMODULE_H
