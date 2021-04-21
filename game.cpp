#include "game.h"
#include <sstream>
#include <algorithm>
#include <iostream>

void game::update_map(float delta_time)
{
    for(auto &i : this->entites)
        i->update(delta_time);
    for(auto &i : this->players)
        i.second.update(delta_time);
    for(auto &i : this->map)
        i->update(delta_time);
}

void game::enter(sf::TcpSocket *sock)
{
    std::cout << "connected:" <<sock->getRemoteAddress().toString() << endl;
    socks.push_back(sock);
    players[sock] = player_tank();
}

void game::read_clinets()
{
    for(sf::TcpSocket* &sock : socks)
    {
        if(sock==nullptr)continue;

        sf::Packet pk;
        auto status = sock->receive(pk);
        if(status == sf::TcpSocket::Done)
        {
            /// reading
        }
        if(status == sf::TcpSocket::Disconnected)
        {
            /// removing socket
            std::cout << "disconnected:" <<sock->getRemoteAddress().toString() << endl;
            players.erase(sock);
            delete sock;
            sock = nullptr;

        }
    }
    auto last = std::remove(socks.begin(),socks.end(),nullptr);
    socks.erase(last,socks.end());
}

void game::send_update()
{
 //players map
    stringstream ss("");
    ss << "players," << players.size() << ',' << player_tank::write_count << ',';
    for(auto &i : players){
        i.second.write_state(ss,',');
        ss << ',';
    }
    ss << "entities," << entites.size() << ',' << entity::write_count << ',';
    for(auto &i : entites){
        i->write_state(ss,',');
        ss << ',';
    }
    ss << "map," << map.size() << ',' << wall::write_count << ',';
    for(auto &i : map){
        i->write_state(ss,',');
        ss << ',';
    }
    sf::Packet pack;
    pack.append(ss.str().c_str(),ss.str().size());

    for(auto &s : socks)
        s->send(pack);
}
