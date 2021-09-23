#ifndef BULLET_H
#define BULLET_H

#include <memory>

#include "math_tools/mvector.h"
#include "object.h"

class Bullet: public Object
{
    unsigned damage;
    const static float speed;
    size_t friend_id;
    friend class BulletModule;
public:
    Bullet(ObjectInterface & interface, Vector position , size_t friend_id , float angle, unsigned damage);

    void Update();

    virtual void Collision(Object *obj , Vector normal);

    friend class player_controller;
};

#endif // BULLET_H
