#include "player_controller.h"
#include "game.h"
#include "debug_tools/out.h"

player_controller::player_controller(channel *c , game *game):
    _channel(c),
    _game(game),
    tank( new Tank(nullptr , "The Ivan Python coder" , 300) )
{
    archive a;
    game->map.write(a);
    std::string data = a.text();
    try {
        this->_channel->send(data.c_str(),data.size());
    }  catch (disconnect_error &e) {
        info("disconnected " + this->tank->name);
        valid = false;
    }
}

void player_controller::update(std::vector<shared_ptr<Tank> > visible_unit)
{
    if(valid == false)
        return;

    archive a;
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

    auto data = a.text();
    try {
        this->_channel->send(data.c_str(),data.size());
    }  catch (disconnect_error &e) {
         info("disconnected " + this->tank->name);
        valid = false;
    }

}

void player_controller::update(std::vector<shared_ptr<Bullet> > bullets)
{
    if(valid == false)
        return;

    archive a;
    a.write("bullets");
    a.write(bullets.size());
    a.write(6);
    for(const auto &i : bullets)
    {
        a.write(i->position.x);
        a.write(i->position.y);
        a.write(i->size.x);
        a.write(i->size.y);
        a.write(i->rotate);
        a.write("bullet.png");
    }
    auto data = a.text();
    try {
        this->_channel->send(data.c_str(),data.size());
    }  catch (disconnect_error &e) {
         info("disconnected " + this->tank->name);
        valid = false;
    }

}

void player_controller::events()
{
    if(valid == false)
        return;

    char data[2048];
    size_t read = 0;


    bool done;
    try {
       done = _channel->read(data,1024 , read);
    }  catch (disconnect_error &e) {
        info("disconnected " + this->tank->name);
        valid = false;
    }
    if(done)
    {
        std::stringstream s;
        s.write(data,read);

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
                debug("set speed " + std::to_string(move) + " " + std::to_string(rotate) + " " + std::to_string(tower_rotate));
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
}
