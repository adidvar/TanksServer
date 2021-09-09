#ifndef BULLET_H
#define BULLET_H

#include <memory>
#include "math_tools/mvector.h"
#include "object.h"

class Bullet: public Object
{
    unsigned damage;
    const static float speed;

public:
    Bullet(ObjectInterface * interface, Vector position, float angle, unsigned damage);

    void Update();

    virtual void Collision(Object *obj , Vector normal);

    friend class player_controller;
};

#endif // BULLET_H