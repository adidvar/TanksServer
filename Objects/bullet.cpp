#include "bullet.h"
#include "collider.h"
#include "tank.h"

const float Bullet::speed = 0.01f;
const int border = 100;

Bullet::Bullet(ObjectInterface &interface, Vector position , std::weak_ptr<Tank> sender, size_t team_id , float angle, unsigned damage):
    RectObject(interface , position , {0.12f , 0.45f} , angle , true),
    damage(damage),
    team_id(team_id),
    sender(sender)
{
}

void Bullet::Update(unsigned delta_time)
{
    this->position = position + Vector::fromVector(speed * delta_time ,rotate);
    if(position.x < -border || position.x > border || position.y < -border || position.y > border){
        this->Suicide();
    }
}

void Bullet::CollisionCycleBegin(unsigned delta_time)
{

}

void Bullet::CollisionCycleEnd(unsigned delta_time)
{

}

void Bullet::CollisionEvent(class Object *object, Vector normal , unsigned delta_time)
{
    if (this->IsValid() == false)
        return;

    if (dynamic_cast<Collider*>(object) != nullptr)
    {
        this->Suicide();
    }
    Tank* tank;
    if ( (tank = dynamic_cast<Tank*>(object)) != nullptr && tank->Team() != this->team_id)
    {
        tank->Damage(this->damage);
        if(tank->IsLive()==false)
            sender.lock()->RegisterKill();
        this->Suicide();
    }
    //if(valid == true)
     //   tank->damage(this->damage);
    //valid = false;
}
