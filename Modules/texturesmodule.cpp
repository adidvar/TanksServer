#include "texturesmodule.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
/*
BeaconModule::BeaconModule(ModuleInterface &interface):
    Module(interface),
    acceptor(interface.Service() , boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(),33335))
{
    acceptor.async_receive_from(boost::asio::buffer(buffer,buffer_size),endpoint ,
                                boost::bind(&BeaconModule::ReadyRead , this ,boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
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

boost::json::object BeaconModule::DefaultSettings() const
{
    boost::json::object root;
    root["name"] = "TanksServer";
    root["description"] = "Someone server for tanks";
    root["version"] = "1.0";
    root["port"] = 33334;
    return root;
}

void BeaconModule::LoadSettings(const boost::json::object &obj)
{
    this->reply = obj;
}
*/


TexturesModule::TexturesModule(ModuleInterface &interface):
    Module(interface),
    acceptor(interface.Service(),boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),8080))
{
    auto *sock = new boost::asio::ip::tcp::socket(interface.Service());
    acceptor.async_accept(*sock , boost::bind(&TexturesModule::Accept , this , sock , boost::asio::placeholders::error));
}

TexturesModule::~TexturesModule()
{

}

const size_t pack_size = 2048;

void TexturesModule::Accept(boost::asio::ip::tcp::socket *socket, const boost::system::error_code &error)
{
    if(error){
        delete socket;
        return;
    }
   char * data = new char[pack_size];
   socket->async_receive(boost::asio::buffer(data,pack_size) , boost::bind(&TexturesModule::ReadyRead , this , socket , data , boost::asio::placeholders::error , boost::asio::placeholders::bytes_transferred));

    auto *sock = new boost::asio::ip::tcp::socket(environment.Service());
    acceptor.async_accept(*sock , boost::bind(&TexturesModule::Accept , this , sock , boost::asio::placeholders::error));
}
auto text =
"HTTP/1.1 200 OK\n"
"Date: Mon, 27 Jul 2009 12:28:53 GMT\n"
"Server: Apache/2.2.14 (Win32)\n"
"Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\n"
"Content-Type: text/html\n"
"Connection: Closed\n";

void TexturesModule::ReadyRead(boost::asio::ip::tcp::socket *socket , char * data , const boost::system::error_code &error, size_t readed)
{
    auto header_end = std::find(data , data+readed , '\n');

    auto first_space = std::find(data , header_end, ' ');
    auto second_space = std::find(first_space +1 , header_end , ' ');

    auto index = "."+std::string(first_space+1 , second_space);

    std::stringstream ss;
    ss << "HTTP/1.1" << (std::filesystem::exists(index) ? std::string_view("200 OK") : std::string_view("404 Not Found") ) << std::endl;

    if(std::filesystem::exists(index)){
        std::ifstream file(index);

        auto size = std::filesystem::file_size(index);
        char *data = new char[size];
        file.read(data,size);

        ss << "Content-Type: image/jpeg\n";
        ss << "Content-Length:" << size;
        ss << "\r\n\r\n";

        auto string = ss.str();

        socket->send(boost::asio::buffer(string.data(),string.size()));
        socket->send(boost::asio::buffer(data,size));

        delete []data;
        file.close();
    }

    std::cout << index << std::endl;

    socket->close();
    delete socket;
    delete data;
}
