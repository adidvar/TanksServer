#ifndef BULLET_H
#define BULLET_H

#include <mvector.h>
#include "rectobject.h"
#include "tank.h"

class Bullet: public RectObject
{
    unsigned damage;
    const static float speed;
    size_t team_id;
    std::weak_ptr<Tank> sender;
public:
    Bullet(ObjectInterface & interface, Vector position , std::weak_ptr<Tank> sender , size_t command_id , float angle, unsigned damage);
    friend class BulletModule;

    void Update(unsigned delta_time) override;

    virtual void CollisionCycleBegin(unsigned delta_time) override;
    virtual void CollisionCycleEnd(unsigned delta_time) override;
    virtual void CollisionEvent(Object *obj , Vector normal , unsigned delta_time) override;
};

#endif // BULLET_H
