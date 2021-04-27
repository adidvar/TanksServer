#include "player_controller.h"
#include "game.h"
#include "out.h"

player_controller::player_controller(channel *c):
    _channel(c)
{

}

void player_controller::start(shared_ptr<tank> tank, game *game)
{
    _tank = tank;
    _game = game;
}

void player_controller::update(std::vector<shared_ptr<tank> > visible_unit)
{
    if(valid == false)
        return;

    archive a;
    a.write("v_tanks");
    a.write(visible_unit.size());
    a.write(8);
    for(auto i : visible_unit)
    {
        a.write(i->Name());
        a.write(i->Team());
        a.write(i->Position().x);
        a.write(i->Position().y);
        a.write(i->Size().x);
        a.write(i->Size().y);
        a.write(i->Angle());
        a.write(i->Tower_angle());
    }
    a.write("main_tank");
    a.write(1);
    a.write(12);
    a.write(_tank->Name());
    a.write(_tank->Team());
    a.write(_tank->Position().x);
    a.write(_tank->Position().y);
    a.write(_tank->Size().x);
    a.write(_tank->Size().y);
    a.write(_tank->Angle());
    a.write(_tank->Tower_angle());
    a.write(_tank->islive());
    a.write(_tank->Current_hp());
    a.write(_tank->Max_hp());
    a.write(typeid (*_tank.get()).name());

    auto data = a.text();
    try {
        this->_channel->send(data.c_str(),data.size());
    }  catch (disconnect_error &e) {
        info("socket error disconnect");
        valid = false;
    }

}

void player_controller::events()
{
    if(valid == false)
        return;

    char data[1024];
    size_t read = 0;

    auto done = _channel->read(data,1024 , read);
    if(done)
    {
        info("Get package");
        std::stringstream s;
        s.write(data,read);

        while(s)
        {
            string name;
            unsigned count , len;
            s >> name >> count >> len;

            if(name == "speed" && count == 1 && len == 2)
            {
                int move , rotate , tower_rotate;
                s >> move >> rotate >> tower_rotate;
                _tank->setmove(move,rotate,tower_rotate);
            }

            if(name == "name" && count == 1 && len == 1)
            {
                std::string name;
                s >> name;
                _tank->setname(name);
            }

        }

    }
}

//    stringstream ss("");
//    ss << "players;" << players.size() << ';' << player_tank::write_count << ';';
//    for(auto &i : players){
//        i.second.write_state(ss,';');
//    }
//    ss << "entities;" << entites.size() << ';' << entity::write_count << ';';
//    for(auto &i : entites){
//        i->write_state(ss,';');
//    }
//    ss << "map;" << map.size() << ';' << wall::write_count << ';';
//    for(auto &i : map){
//        i->write_state(ss,';');
//    }

//    size_t sended = 0;
//    for(auto &s : socks)
//        s->send(ss.str().c_str(),ss.str().size(),sended);
