#include "bulletmodule.h"

const unsigned delay = 10;

BulletModule::BulletModule(ModuleInterface &interface):
    Module(interface),
    update_timer(interface.Service(),boost::posix_time::millisec(delay))
{
}

void BulletModule::Start()
{
    update_timer.async_wait(boost::bind(&BulletModule::Update,this,boost::asio::placeholders::error));
}

void BulletModule::SpawnBullet(std::shared_ptr<Bullet> bullet)
{
    bullets.push_back(bullet);
    environment.Physics().Push(bullet);
}

boost::json::object BulletModule::GenerateBulletJson(const std::shared_ptr<Bullet> &bullet)
{
    boost::json::object bulletjson;
    bulletjson["x"] = bullet->position.x;
    bulletjson["y"] = bullet->position.y;
    bulletjson["size_x"] = bullet->size.x;
    bulletjson["size_y"] = bullet->size.y;
    bulletjson["rotate"] = bullet->rotate;
    bulletjson["team_id"] = bullet->friend_id;
    return bulletjson;
}

boost::json::object BulletModule::GenerateJson()
{
    boost::json::object root;
    boost::json::array bullets;
    for(const auto& bullet : bullets)
        bullets.push_back(bullet);
    root["type"] = "bullets";
    root["users"] = bullets;
    return root;
}

void BulletModule::Update(const boost::system::error_code &)
{ 
    {   ///< Видалення закритих зєднанн
        auto it = remove_if(bullets.begin(),bullets.end(),[](const std::shared_ptr<Bullet> p){return !p->IsValid();});
        bullets.erase(it,bullets.end());
    }

    auto package = boost::json::serialize(GenerateJson());

    update_timer.expires_from_now(boost::posix_time::millisec(delay));
    update_timer.async_wait(boost::bind(&BulletModule::Update,this , boost::asio::placeholders::error));
}
