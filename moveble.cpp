#include "moveble.h"
#include <math.h>
#include <sstream>

moveble::moveble(float x, float y, float rotation, float size_x, float size_y , float speed, float rotate_speed):
    x(x),
    y(y),
    rotation(rotation),
    rotate_speed(rotate_speed),
    size_x(size_x),
    size_y(size_y),
    speed(speed)
{

}

moveble::moveble(stringstream &ss , float speed , float rotate_speed)
{
  this->speed = speed;
  this->rotate_speed = rotate_speed;
  ss >> x >> y >> rotation >> size_x >> size_y;
}

void moveble::setspeed(float speed, float rspeed)
{
    this->speed = speed;
    this->rotate_speed = rspeed;
}

void moveble::update(unsigned delta_time)
{
    x+= cos(rotation)*delta_time*speed;
    y+= sin(rotation)*delta_time*speed;
    rotation += rotate_speed*delta_time;
}

std::string moveble::todata()
{
    std::stringstream ss;
    ss << x << " ";
    ss << y << " ";
    ss << rotation << " ";
    ss << size_x << " ";
    ss << size_y;
    return ss.str();
}
