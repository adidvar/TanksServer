#include "player_controller.h"

#include <boost/json/src.hpp>

#include <out.h>

player_controller::player_controller(ObjectInterface &interface , tcp::socket *sock):
    channel(sock),
    tank( new  Tank(interface , "The Ivan Python coder" , 300) ),
    valid(true)
{ 
    this->channel->async_read_some(boost::asio::buffer(buffer, buffer_size), boost::bind(&player_controller::readyread, this, boost::asio::placeholders::error , boost::asio::placeholders::bytes_transferred));
}

player_controller::~player_controller()
{
    if(valid==true)
    {
        destroy();
        channel->close();
    }
}

void player_controller::destroy()
{
    valid = false;
    channel->cancel();
    tank->Suicide();
    info("disconnect");
}

boost::json::object player_controller::GetPlayerJson() const
{
    boost::json::object tankjson;
    tankjson["name"] = tank->name;
    tankjson["team_id"] = tank->team_id;
    tankjson["x"] = tank->position.x;
    tankjson["y"] = tank->position.y;
    tankjson["size_x"] = tank->size.x;
    tankjson["size_y"] = tank->size.y;
    tankjson["rotate"] = tank->rotate;
    tankjson["tower_angle"] = tank->tower_angle;
    tankjson["live"] = tank->IsLive();
    tankjson["health"] = tank->health;
    tankjson["health_max"] = tank->health_max;
    return tankjson;
}

void player_controller::send(std::string data)
{
    if(valid==false)
        return;

    boost::system::error_code code;
    this->channel->send(boost::asio::buffer(data.c_str(), data.size()), 0, code);
    if (code)
    {
        warning(code.message());
        destroy();
        return;
    }
}

void player_controller::readyread(const boost::system::error_code &code , size_t bytes_transfered)
{
    if (valid == false)
        return;
    if(code){
        warning(code.message());
        destroy();
        return;
    }

    std::stringstream s;
    s.write(buffer,bytes_transfered);

    while(s)
    {
        string name;
        unsigned count , len;
        s >> name >> count >> len;

        if(name == "speed" && count == 1 && len == 3)
        {
            int move , rotate , tower_rotate;
            s >> move >> rotate >> tower_rotate;
            tank->SetMove(move,rotate,tower_rotate);
        }
        else if(name == "name" && count == 1 && len == 1)
        {

            std::string name;
            s >> name;
            debug("set name " + name);
            tank->name = name;
        } else if (name == "fire" && count == 1 && len == 1)
        {
            debug("fire");
            tank->Fire();
        }
        else if (name == "")
        {} else
        {
            warning("unsupported package command" + name);
        }

    }
    this->channel->async_read_some(boost::asio::buffer(buffer, buffer_size), boost::bind(&player_controller::readyread, this, boost::asio::placeholders::error , boost::asio::placeholders::bytes_transferred));
}
