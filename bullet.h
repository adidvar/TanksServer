#ifndef BULLET_H
#define BULLET_H

#include <math_tools/rect.h>
#include <memory>
#include <tank.h>

class Tank;

class Bullet: public rect
{
    unsigned damage;
    bool valid = true;
public:

    using Ptr = std::shared_ptr<Bullet>;

    Bullet(unsigned damame);

    bool is_valid(){return valid;};

    void Collision(std::shared_ptr<Tank> tank , Vector2f normal );
};

#endif // BULLET_H
