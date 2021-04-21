#include "tank.h"

void player_tank::update(unsigned delta_time)
{
    positions = positions + speed*delta_time;
}

void player_tank::write_state(stringstream &s , char sep)
{
    s << name << sep << positions.x << sep << positions.y << sep << rotation << sep;
}

void player_tank::read_state(stringstream &s)
{
    while(s)
    {
        string name;
        unsigned count , len;
        s >> name >> count >> len;

        if(name == "speed" && count == 1 && len == 1)
        {
            Vector2f vect;
            s >> vect.x >> vect.y;
            this->speed = vect;
        }
    }
}
