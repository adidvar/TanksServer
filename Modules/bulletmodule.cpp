#include "bulletmodule.h"

static std::chrono::milliseconds delay{ 10 };

BulletModule::BulletModule(ModuleInterface &interface):
    Module(interface),
    update_timer(interface.Service(),delay)
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
    bulletjson["team_id"] = bullet->team_id;
    return bulletjson;
}

boost::json::object BulletModule::GenerateJson()
{
    boost::json::object root;
    boost::json::array bullets;
    for(const auto& bullet : this->bullets)
        bullets.push_back(GenerateBulletJson(bullet));
    root["type"] = "bullets";
    root["bullets"] = bullets;
    return root;
}

boost::json::object BulletModule::DefaultSettings() const
{
   boost::json::object set;
   set["delay"] = delay.count();
   return set;
}

void BulletModule::LoadSettings(const boost::json::object &obj)
{
    auto copy = obj;
    delay = std::chrono::milliseconds{copy["delay"].as_int64()};
}

void BulletModule::Update(const boost::system::error_code &)
{ 
    {   ///< Видалення закритих зєднанн
        auto it = remove_if(bullets.begin(),bullets.end(),[](const std::shared_ptr<Bullet> p){return !p->IsValid();});
        bullets.erase(it,bullets.end());
    }

    std::string package = boost::json::serialize(GenerateJson()) + '\n';
    environment.SendEvent(BroadCastEvent{package});

    update_timer.expires_at(std::chrono::steady_clock::now() + delay);
    update_timer.async_wait(boost::bind(&BulletModule::Update,this , boost::asio::placeholders::error));
}
