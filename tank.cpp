#include "tank.h"
#include "debug_tools/out.h"

#include <math.h>

const float move_speed = -0.02;
const float rotation_speed = 0.03;
const float tower_speed = 0.02;

tank::tank():
    rect{{0,0},{2,1},0}
{

}

tank::~tank()
{
}

void tank::update(unsigned delta_time)
{
    position = position + Vector2f::fromVector(position_direction * move_speed , sin(rotate) , cos(rotate));
    rotate += angle_direction * rotation_speed;
    tower_angle += tower_angle_direction * tower_speed + angle_direction * rotation_speed;
}

void tank::setname(string name)
{
    this->name = name;
}

void tank::setmove(int move, int rotation, int tower_rotation)
{
    this->position_direction = move;
    this->angle_direction = rotation;
    this->tower_angle_direction = tower_rotation;
}

void tank::start(Vector2f position, size_t team_id)
{
    this->position = position;
    this->team_id = team_id;
}

bool tank::islive()
{
    return current_hp > 0;
}

std::vector<line> tank::Split()
{
    return rect::Split();
}

void tank::Collision(map_rect *rect, Vector2f normal)
{
    position = position+ normal*(-move_speed);
}

void tank::Collision(shared_ptr<tank>, Vector2f normal)
{
    if(this->position_direction != 0)
        position = position+ normal*(-move_speed);
}

void tank::damage(unsigned damage)
{
    current_hp -= damage;
}

Vector2f tank::Position()
{
    return position;
}

Vector2f tank::Size()
{
    return size;
}

float tank::Angle()
{
    return rotate;
}

float tank::Tower_angle()
{
    return tower_angle;
}

int tank::Max_hp()
{
    return max_hp;
}

int tank::Current_hp()
{
    return current_hp;
}

size_t tank::Team()
{
    return team_id;
}

string tank::Name()
{
    return name;
}
