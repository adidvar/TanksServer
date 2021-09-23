#include "bulletmodule.h"

const unsigned delay = 10;

BulletModule::BulletModule(ModuleInterface &interface):
    Module(interface),
    update_timer(interface.service,boost::posix_time::millisec(delay))
{
}

void BulletModule::Start()
{
    update_timer.async_wait(boost::bind(&BulletModule::Update,this,boost::asio::placeholders::error));
}

void BulletModule::SpawnBullet(std::shared_ptr<Bullet> bullet)
{
    bullets.push_back(bullet);
    environment.container.Push(bullet);
}

void BulletModule::Write(archive& a)
{
    a.write("bullets");
    a.write(this->bullets.size());
    a.write(6);
    for(const auto &i : this->bullets)
    {
        a.write(i->position.x);
        a.write(i->position.y);
        a.write(i->size.x);
        a.write(i->size.y);
        a.write(i->rotate);
        a.write("bullet");  
    }
    a.packend();
}

void BulletModule::Update(const boost::system::error_code &)
{ 
    {   ///< Видалення закритих зєднанн
        auto it = remove_if(bullets.begin(),bullets.end(),[](const std::shared_ptr<Bullet> p){return !p->IsValid();});
        bullets.erase(it,bullets.end());
    }
    update_timer.expires_from_now(boost::posix_time::millisec(delay));
    update_timer.async_wait(boost::bind(&BulletModule::Update,this , boost::asio::placeholders::error));
}
