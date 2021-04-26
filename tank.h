#ifndef TANK_H
#define TANK_H
#include <string>
#include <vector2f.h>
#include <functional>

using namespace std;

class tank
{
    string name = "NoName";
    size_t team_id = 0;

    Vector2f position = {0,0};
    const Vector2f size = {2,1};
    float angle = 0.0;
    float tower_angle = 0.0;

    int position_direction = 0;
    int angle_direction = 0;
    int tower_angle_direction = 0;

    int max_hp = 300;
    int current_hp = 300;

public:
    tank() = default;
    void update(unsigned delta_time);

    void setname(std::string name);
    void setmove(int move , int  rotation , int tower_rotation);
    void fire();

    void start(Vector2f position , size_t team_id);
    bool islive();

    [[deprecated]] /// < сигнатура крива треба реєструвати потенціальні фраги
    void damage(unsigned damage);

    Vector2f Position();
    Vector2f Size();
    float Angle();
    float Tower_angle();
    int Max_hp();
    int Current_hp();
    size_t Team();
    std::string Name();
};

#endif // TANK_H
