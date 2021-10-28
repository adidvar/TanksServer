#include "beaconmodule.h"

BeaconModule::BeaconModule(ModuleInterface &interface):
    Module(interface),
    acceptor(interface.Service() , boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(),33335))
{
    acceptor.async_receive_from(boost::asio::buffer(buffer,buffer_size),endpoint ,
                                boost::bind(&BeaconModule::ReadyRead , this ,boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

BeaconModule::~BeaconModule()
{

}

boost::json::object BeaconModule::GenerateJson()
{
    boost::json::object root;
    root["name"] = "TanksServer";
    root["description"] = "Someone server for tanks";
    root["version"] = "1.0";
    root["port"] = 33334;
    return root;
}

void BeaconModule::ReadyRead(const boost::system::error_code &error, size_t transfered)
{
    if(error){
        return;
    }

    auto root = this->GenerateJson();
    auto text = boost::json::serialize(root);

    acceptor.send_to(boost::asio::buffer(text.data(),text.size()),this->endpoint);

    acceptor.async_receive_from(boost::asio::buffer(buffer,buffer_size),endpoint ,
                                boost::bind(&BeaconModule::ReadyRead , this ,boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

