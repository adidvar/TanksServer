#ifndef BULLETMODULE_H 
#define BULLETMODULE_H 

#include <vector>
#include <memory>

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/json.hpp>

#include <bullet.h>

#include "module.h"
#include "playermodule.h"

class BulletModule: public Module
{
    std::vector<std::shared_ptr<Bullet>> bullets; ///< контролери
    boost::asio::steady_timer update_timer;
public:
    BulletModule(ModuleInterface &interface);

    virtual void Start() override;
    void SpawnBullet(std::shared_ptr<Bullet> bullet);
    boost::json::object GenerateBulletJson(const std::shared_ptr<Bullet> &bullet);
    boost::json::object GenerateJson();

    virtual boost::json::object DefaultSettings() const override;
    virtual void LoadSettings(const boost::json::object &obj) override;


private:
    void Update(const boost::system::error_code&);
};

#endif // PLAYERMODULE_H
