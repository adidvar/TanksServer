#include "player_controller.h"

#include <boost/json/src.hpp>

#include <out.h>

player_controller::player_controller(ObjectInterface &interface , tcp::socket *sock):
    channel(sock),
    tank( new  Tank(interface , "The Ivan Python coder" , 300) ),
    valid(true)
{ 
    this->channel->async_read_some(boost::asio::buffer(read_buffer, buffer_size), boost::bind(&player_controller::readyread, this, boost::asio::placeholders::error , boost::asio::placeholders::bytes_transferred));
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
    boost::json::object prediction_obj;
    prediction_obj["move_speed"] = Tank::move_speed;
    prediction_obj["rotate_speed"] = Tank::rotation_speed;
    prediction_obj["tower_speed"] = Tank::tower_speed;
    prediction_obj["move_direction"] = tank->controller.position_direction;
    prediction_obj["rotate_direction"] = tank->controller.angle_direction;
    prediction_obj["tower_direction"] = tank->controller.tower_angle_direction;
    tankjson["prediction"] = prediction_obj;
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

    this->input_buffer.append(read_buffer,bytes_transfered);

    auto pack_end = std::find(input_buffer.begin(),input_buffer.end(),'\n');
    if(pack_end == input_buffer.end())
        return;

    std::string json(input_buffer.begin(),pack_end);
    input_buffer.erase(input_buffer.begin(),pack_end+1);

    boost::json::value root = boost::json::parse(json);
    boost::json::object root_obj = root.as_object();

    auto type = root_obj["type"].as_string();
    if(type == "speed")
    {
            int move = root_obj["move_direction"].as_int64() ,
                    rotate = root_obj["rotate_direction"].as_int64() ,
                    tower_rotate = root_obj["tower_direction"].as_int64();
            tank->SetMove(move,rotate,tower_rotate);
    }else if(type == "name")
    {
           std::string name = root_obj["name"].as_string().c_str();
            debug("set name " + name);
            tank->name = name;

    } else if(type =="fire")
    {
           debug("fire");
            tank->Fire();
    } else {
        warning(std::string("unsupported package command ") + type.c_str());
    }

    this->channel->async_read_some(boost::asio::buffer(read_buffer, buffer_size), boost::bind(&player_controller::readyread, this, boost::asio::placeholders::error , boost::asio::placeholders::bytes_transferred));
}
