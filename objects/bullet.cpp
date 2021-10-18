#include "bullet.h"
#include "collider.h"
#include "tank.h"

const float Bullet::speed = 0.3f;

Bullet::Bullet(ObjectInterface &interface, Vector position , size_t friend_id , float angle, unsigned damage):
    Object(interface , position , {0.12f , 0.45f} , angle , true),
    damage(damage),
    friend_id(friend_id)
{
}

void Bullet::Update()
{
    this->position = position + Vector::fromVector(speed,rotate);
}

void Bullet::Collision(class Object *object, Vector normal)
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
