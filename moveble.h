#ifndef MOVEBLE_H
#define MOVEBLE_H
#include "entity.h"
#include <sstream>

using namespace std;

class moveble : public entity
{
    float x;
    float y;
    float rotation;
    float rotate_speed;
    float size_x;
    float size_y;
    float speed;
public:
    moveble(float x,float y ,float rotation,float size_x,float size_y,float speed , float rotate_speed);
    moveble(stringstream &ss, float speed , float rotate_speed); // from data;

    void setspeed(float speed , float rspeed);

    virtual void update(unsigned delta_time) override;
    virtual std::string todata() override; // to data
};

#endif // MOVEBLE_H
