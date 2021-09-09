#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include <memory>

#include "tank.h"
#include "bullet.h"
#include "archive.h"
#include "channel.h"
#include <memory>

class game;


/**
 * @brief Клас який прив'язується до танка і проводити керування ним , в нашому випадку приймає і читає інформацію через канал
 */
class player_controller
{
    std::unique_ptr<channel> _channel;
    std::shared_ptr<Tank> tank;
    bool valid = true;
    void destroy();
public:
    player_controller(channel *c , std::shared_ptr<Map> map);
    /**
     * @brief оновлення інформації
     * @param visible_unit юніти які попадають в обзор
     */
    void update(std::vector<std::shared_ptr<Tank>> visible_unit); ///< відправка нової інформації
    /**
     * @brief events обробка інформації яка приходить
     */
    void update(std::vector<std::shared_ptr<Bullet>> bullets); ///< відправка нової інформації


    void events(); ///< обробка того що прийшло від клієнта

    bool is_valid(){return valid;}

    std::shared_ptr<Tank> GetTank(){return tank;};
};

#endif // PLAYER_CONTROLLER_H
