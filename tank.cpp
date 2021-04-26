#include "tank.h"
#include "math.h"

void player_tank::update(unsigned delta_time)
{
    positions = positions + Vector2f::fromVector(speed.x , cos(rotation) , sin(rotation));
    rotation +=  speed.y*0.02;
}

void player_tank::write_state(stringstream &s , char sep)
{
    s << name << sep << positions.x << sep << positions.y << sep << rotation << sep << team_id << sep;
}

void player_tank::read_state(stringstream &s)
{
    while(s)
    {
        string name;
        unsigned count , len;
        s >> name >> count >> len;

        if(name == "speed" && count == 1 && len == 2)
        {
            Vector2f vect;
            s >> vect.x >> vect.y;
            this->speed = vect;
        }
        if(name == "name" && count == 1 && len == 1)
        {
            std::string name;
            s >> name;
            this->name = name;
        }
    }
}
