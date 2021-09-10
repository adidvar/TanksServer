#include "bullet.h"

Bullet::Bullet(ObjectInterface &interface, Vector position , float angle, unsigned damage):
    Object(interface , position , {0.5f , 0.5f} , angle , true),
    damage(damage)
{
}

void Bullet::Update()
{
    this->position = position;
}

void Bullet::Collision(Object *tank, Vector normal)
{
    //if(valid == true)
     //   tank->damage(this->damage);
    //valid = false;
}
