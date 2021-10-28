#ifndef TANK_H
#define TANK_H

#include <string>
#include <memory>
#include <mvector.h>

#include "object.h"

class Tank : public Object
{
protected:
    std::string name = "NoName";
    size_t team_id = 0;
    float tower_angle = 0.0;

    struct Controller
    {
        float position_direction = 0;
        float angle_direction = 0;
        float tower_angle_direction = 0;
    } controller;

    int health = 300;
    int health_max = 300;

    static float move_speed;
    static float rotation_speed;
    static float tower_speed;

public:
    Tank(ObjectInterface & interface , std::string name, int health_max);

    virtual void Update(unsigned delta_time) override;

    void Spawn(Vector position , size_t team_id);
    void SetMove(int move , int  rotation , int tower_rotation);
    void Fire();
    size_t Team();
    bool IsLive();

    virtual void CollisionCycleBegin(unsigned delta_time) override;
    virtual void CollisionCycleEnd(unsigned delta_time) override;

    virtual void CollisionEvent(Object *obj , Vector normal , unsigned delta_time) override;
    virtual MultiPointShape Poligon() const override;

    [[deprecated]] /// < сигнатура крива треба реєструвати потенціальні фраги
    void Damage(unsigned damage);

    friend class player_controller;
};

#endif // TANK_H
