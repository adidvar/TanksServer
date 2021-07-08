#include "bullet.h"

Bullet::Bullet(unsigned dam):
    damage(dam)
{

}

void Bullet::Collision(std::shared_ptr<Tank> tank, Vector2f normal)
{
    if(valid == true)
        tank->damage(this->damage);
    valid = false;
}
