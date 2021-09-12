#include "bullet.h"
#include "map.h"

const float Bullet::speed = 0.1f;

Bullet::Bullet(ObjectInterface &interface, Vector position , float angle, unsigned damage):
    Object(interface , position , {0.5f , 0.5f} , angle , true),
    damage(damage)
{
}

void Bullet::Update()
{
    this->position = position + Vector::fromVector(speed,rotate);
}

void Bullet::Collision(Object *tank, Vector normal)
{
    if (dynamic_cast<Decor*>(tank) != nullptr)
    {
        this->Suicide();
    }

    //if(valid == true)
     //   tank->damage(this->damage);
    //valid = false;
}
