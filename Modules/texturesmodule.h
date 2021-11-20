#ifndef TEXTURESMODULE_H
#define TEXTURESMODULE_H

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/json.hpp>

#include "module.h"

class TexturesModule : public Module
{
    boost::asio::ip::tcp::acceptor acceptor;
public:
    TexturesModule(ModuleInterface &interface);
    virtual ~TexturesModule() override;
    virtual void Start() override {};
    virtual void Event(std::any &event) override {};
private:
    void Accept(boost::asio::ip::tcp::socket *socket , const boost::system::error_code &error);
    void ReadyRead(boost::asio::ip::tcp::socket *socket , char* data , const boost::system::error_code &error , size_t readed);

    virtual boost::json::object DefaultSettings()const override { return {};};
    virtual void LoadSettings(const boost::json::object &obj) override {};
};

#endif // TEXTURESMODULE_H
