#ifndef GAME_H
#define GAME_H
#include "tank.h"
#include "wall.h"
#include "entity.h"
#include <vector>
#include <unordered_map>
#include <memory>
#include <SFML/Network.hpp>

using namespace std;

class wall;

class game
{
    vector<wall*> map; ///< об'єкти карти
    vector<entity*> entites; ///< різні створіння
    unordered_map<sf::TcpSocket*,player_tank> players; ///< бідінги сокетів до гравців
    vector<sf::TcpSocket*> socks; ///< список сокетів
public:
    game() = default;
    void update_map(float delta_time);
    void enter(sf::TcpSocket *sock);
    void read_clinets();
    void send_update();
    void load_map() = delete;
};

#endif // GAME_H
