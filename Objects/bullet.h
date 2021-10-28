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

    virtual void CollisionCycleBegin() override;
    virtual void CollisionCycleEnd() override;
    virtual void CollisionEvent(Object *obj , Vector normal) override;
};

#endif // BULLET_H
