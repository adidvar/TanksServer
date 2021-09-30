#include "player_controller.h"

#include "../debug_tools/out.h"
#include "archive.h"

void player_controller::destroy()
{
    valid = false;
    tank->Suicide();
}

player_controller::player_controller(ObjectInterface &interface , std::unique_ptr<tcp::socket> c):
    channel(std::move(c)),
    tank( new  Tank(interface , "The Ivan Python coder" , 300) )
{ 
    this->channel->async_read_some(boost::asio::buffer(buffer, buffer_size), boost::bind(&player_controller::readyread, this, boost::asio::placeholders::error , boost::asio::placeholders::bytes_transferred));
}

void player_controller::update(std::vector<shared_ptr<Tank> > visible_unit)
{
    if(valid == false)
        return;
    if (tank->IsLive() == false)
        tank->Spawn({ 0,0 }, rand());

    archive a;
    a.write("table");
    a.write("v_tanks");
    a.write(visible_unit.size());
    a.write(8);
    for(const auto &i : visible_unit)
    {
        a.write(i->name);
        a.write(i->team_id);
        a.write(i->position.x);
        a.write(i->position.y);
        a.write(i->size.x);
        a.write(i->size.y);
        a.write(i->rotate);
        a.write(i->tower_angle);
    }
    a.packend();
    a.write("table");
    a.write("main_tank");
    a.write(1);
    a.write(12);
    a.write(tank->name);
    a.write(tank->team_id);
    a.write(tank->position.x);
    a.write(tank->position.y);
    a.write(tank->size.x);
    a.write(tank->size.y);
    a.write(tank->rotate);
    a.write(tank->tower_angle);
    a.write(1); // live
    a.write(tank->health);
    a.write(tank->health_max);
    a.write(typeid (*tank.get()).name());
    a.packend();

    auto data = a.text();
    boost::system::error_code code;
    this->channel->send(boost::asio::buffer(data.c_str(),data.size()),0,code);
    if (code)
    {
        info("disconnected " + this->tank->name);
        destroy();
    }
}

void player_controller::send(std::string data)
{
    boost::system::error_code code;
    this->channel->send(boost::asio::buffer(data.c_str(), data.size()), 0, code);
    if (code)
    {
        info("disconnected " + this->tank->name);
        destroy();
    }
}

void player_controller::readyread(const boost::system::error_code &code , size_t bytes_transfered)
{
    if (valid == false)
        return;

    if(!code)
    {
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

    }
    this->channel->async_read_some(boost::asio::buffer(buffer, buffer_size), boost::bind(&player_controller::readyread, this, boost::asio::placeholders::error , boost::asio::placeholders::bytes_transferred));
}
