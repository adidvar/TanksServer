#ifndef BULLETMODULE_H 
#define BULLETMODULE_H 

#include <vector>
#include <memory>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "module.h"
#include "bullet.h"
#include "net/archive.h"

class BulletModule: public Module
{
    std::vector<std::shared_ptr<Bullet>> bullets; ///< контролери
    boost::asio::deadline_timer update_timer;
public:
    BulletModule(ModuleInterface &interface);

    virtual void Start() override;
    void SpawnBullet(std::shared_ptr<Bullet> bullet);
    void Write(archive &arc);
private:
    void Update(const boost::system::error_code&);
};

#endif // PLAYERMODULE_H
