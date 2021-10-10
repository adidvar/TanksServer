#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include <memory>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "../objects/tank.h"

using boost::asio::ip::tcp;

const size_t buffer_size = 1024;

/**
 * @brief Клас який прив'язується до танка і проводити керування ним , в нашому випадку приймає і читає інформацію через канал
 */
class player_controller
{
    std::unique_ptr<tcp::socket> channel;
    std::shared_ptr<Tank> tank;
    bool valid = true;
    void destroy();

    char buffer[buffer_size];
public:
    player_controller(ObjectInterface &interface, std::unique_ptr<tcp::socket>  );
    /**
     * @brief оновлення інформації
     * @param visible_unit юніти які попадають в обзор
     */
    void update(std::vector<std::shared_ptr<Tank>> visible_unit); ///< відправка нової інформації
    /**
     * @brief events обробка інформації яка приходить
     */
    void send(std::string data);

    void readyread(const boost::system::error_code &code , size_t bytes_transfered); ///< обробка того що прийшло від клієнта

    bool is_valid(){return valid;}

    std::shared_ptr<Tank> GetTank(){return tank;};
};

#endif // PLAYER_CONTROLLER_H
