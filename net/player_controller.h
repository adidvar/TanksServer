#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "tank.h"
#include "archive.h"
#include "channel.h"

class player_controller;
class game;

/**
 * @brief Клас який прив'язується до танка і проводити керування ним , в нашому випадку приймає і читає інформацію через канал
 */
class player_controller
{
    unique_ptr<channel> _channel;
    shared_ptr<tank> _tank;
    game * _game;
    bool valid = true;
public:
    player_controller(channel *c);
    /**
     * @brief Запуск контролера
     * @param tank танк
     * @param game ігровий клас
     */
    void start(shared_ptr<tank> tank , game * game);
    /**
     * @brief оновлення інформації
     * @param visible_unit юніти які попадають в обзор
     */
    void update(std::vector<shared_ptr<tank>> visible_unit); ///< відправка нової інформації
    /**
     * @brief events обробка інформації яка приходить
     */
    void events(); ///< обробка того що прийшло від клієнта

    bool is_valid(){return valid;}
};

#endif // PLAYER_CONTROLLER_H
