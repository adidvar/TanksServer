#include "bullet.h"
#include "collider.h"
#include "tank.h"

const float Bullet::speed = 0.01f;
const int border = 100;

Bullet::Bullet(ObjectInterface &interface, Vector position , size_t friend_id , float angle, unsigned damage):
    Object(interface , position , {0.12f , 0.45f} , angle , true),
    damage(damage),
    friend_id(friend_id)
{
}

void Bullet::Update(unsigned delta_time)
{
    this->position = position + Vector::fromVector(speed * delta_time ,rotate);
    if(position.x < -border || position.x > border || position.y < -border || position.y > border){
        this->Suicide();
    }
}

void Bullet::CollisionCycleBegin()
{

}

void Bullet::CollisionCycleEnd()
{

}

void Bullet::CollisionEvent(class Object *object, Vector normal)
{
    if (this->IsValid() == false)
        return;

    if (dynamic_cast<Collider*>(object) != nullptr)
    {
        this->Suicide();
    }
    Tank* tank;
    if ( (tank = dynamic_cast<Tank*>(object)) != nullptr && tank->Team() != this->friend_id)
    {
        tank->Damage(this->damage);
        this->Suicide();
    }
    //if(valid == true)
     //   tank->damage(this->damage);
    //valid = false;
}
