#ifndef BULLET_H
#define BULLET_H

#include <mvector.h>
#include "object.h"

class Bullet: public Object
{
    unsigned damage;
    const static float speed;
    size_t friend_id;
public:
    Bullet(ObjectInterface & interface, Vector position , size_t friend_id , float angle, unsigned damage);

    void Update();

    virtual void Collision(Object *obj , Vector normal);
};

#endif // BULLET_H
