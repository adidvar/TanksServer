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

        char data[1024];
        size_t size = 0;
        
        auto status = sock->receive(data,1024 , size);
        if(status == sf::TcpSocket::Done)
        {
            std::cout << "Package from: " << sock->getRemoteAddress().toString() << std::endl;
            std::stringstream s;
            s.write(data,size);
            players[sock].read_state(s);
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
    ss << "players;" << players.size() << ';' << player_tank::write_count << ';';
    for(auto &i : players){
        i.second.write_state(ss,';');
    }
    ss << "entities;" << entites.size() << ';' << entity::write_count << ';';
    for(auto &i : entites){
        i->write_state(ss,';');
    }
    ss << "map;" << map.size() << ';' << wall::write_count << ';';
    for(auto &i : map){
        i->write_state(ss,';');
    }
    
    size_t sended = 0;
    for(auto &s : socks)
        s->send(ss.str().c_str(),ss.str().size(),sended);
}
