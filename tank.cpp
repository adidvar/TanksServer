#include "tank.h"
#include "debug_tools/out.h"

#include <math.h>

const float move_speed = -0.02;
const float rotation_speed = 0.03;
const float tower_speed = 0.02;

Tank::Tank():
    rect{{0,0},{2,1},0}
{

}

Tank::~Tank()
{
}

void Tank::update(unsigned delta_time)
{
    position = position + Vector2f::fromVector(position_direction * move_speed , sin(rotate) , cos(rotate));
    rotate += angle_direction * rotation_speed;
    tower_angle += tower_angle_direction * tower_speed + angle_direction * rotation_speed;
}

void Tank::setname(string name)
{
    this->name = name;
}

void Tank::setmove(int move, int rotation, int tower_rotation)
{
    this->position_direction = move;
    this->angle_direction = rotation;
    this->tower_angle_direction = tower_rotation;
}

void Tank::start(Vector2f position, size_t team_id)
{
    this->position = position;
    this->team_id = team_id;
}

bool Tank::islive()
{
    return current_hp > 0;
}

std::vector<line> Tank::Split()
{
    return rect::Split();
}

void Tank::Collision(map_rect *rect, Vector2f normal)
{
    info("Coll");
    position = position+ normal*(-move_speed);
}

void Tank::Collision(shared_ptr<Tank>, Vector2f normal)
{
    if(this->position_direction != 0)
        position = position+ normal*(-move_speed);
}

void Tank::Collision(shared_ptr<Bullet>, Vector2f normal)
{

}

void Tank::damage(unsigned damage)
{
    current_hp -= damage;
}

Vector2f Tank::Position()
{
    return position;
}

Vector2f Tank::Size()
{
    return size;
}

float Tank::Angle()
{
    return rotate;
}

float Tank::Tower_angle()
{
    return tower_angle;
}

int Tank::Max_hp()
{
    return max_hp;
}

int Tank::Current_hp()
{
    return current_hp;
}

size_t Tank::Team()
{
    return team_id;
}

string Tank::Name()
{
    return name;
}
