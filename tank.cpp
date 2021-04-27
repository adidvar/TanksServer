#include "tank.h"
#include "math.h"

const float move_speed = 2.0;
const float rotation_speed = 2.0;
const float tower_speed = 2.0;

void tank::update(unsigned delta_time)
{
    position = position + Vector2f::fromVector(position_direction * move_speed , cos(angle) , sin(angle));
    angle += angle_direction * rotation_speed;
    tower_angle +=  tower_angle_direction * tower_speed;
}

void tank::setname(string name)
{
    this->name = name;
}

void tank::setmove(int move, int rotation, int tower_rotation)
{
    this->position_direction = move;
    this->angle_direction = rotation;
    this->tower_angle = tower_rotation;
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
    return angle;
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

//void player_tank::write_state(stringstream &s , char sep)
//{
//    s << name << sep << positions.x << sep << positions.y << sep << rotation << sep << team_id << sep;
//}
