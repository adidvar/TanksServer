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
    friend class BulletModule;

    void Update(unsigned delta_time) override;

    virtual void CollisionCycleBegin(unsigned delta_time) override;
    virtual void CollisionCycleEnd(unsigned delta_time) override;
    virtual void CollisionEvent(Object *obj , Vector normal , unsigned delta_time) override;
};

#endif // BULLET_H
