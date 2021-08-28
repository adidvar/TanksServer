#ifndef TANK_H
#define TANK_H

#include <string>
#include <functional>

#include "object.h"
#include "map.h"
#include "math_tools/mvector.h"
#include <memory>

class Tank : public Object
{
protected:
    std::string name = "NoName";
    size_t team_id = 0;

    float tower_angle = 0.0;

    struct Controller
    {
        int position_direction = 0;
        int angle_direction = 0;
        int tower_angle_direction = 0;
    } controller;

    int health = 300;
    int health_max = 300;

public:
    Tank(ObjectInterface * interface , std::string name , int health_max);

    virtual void Update() override;

    void Spawn(Vector position , size_t team_id);
    void SetMove(int move , int  rotation , int tower_rotation);
    void Fire();

    virtual void Collision(Object *obj , Vector normal) override;
    virtual MultiPointShape Poligon() const override;

    [[deprecated]] /// < сигнатура крива треба реєструвати потенціальні фраги
    void Damage(unsigned damage);

    friend class player_controller;
};

#endif // TANK_H
