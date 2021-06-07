#include "rect.h"

std::vector<line> rect::Split() const
{
    Vector2f points[4] = {
        {size.x/2.0f , size.y/2.0f},
        {size.x/2.0f , -size.y/2.0f},
        {-size.x/2.0f , -size.y/2.0f},
        {-size.x/2.0f , size.y/2.0f}
    };
    float s = sin(rotate) , c = cos(rotate);
    for(size_t i = 0 ;i < 4 ; i++)
    {
        points[i] = points[i].Rotate(-c,-s);
        points[i] = points[i] + Vector2f{position.x,position.y};
    }
    return std::vector<line>{
        line{points[0],points[1]},
        line{points[1],points[2]},
        line{points[2],points[3]},
        line{points[3],points[0]},
    };
}

float rect::Radius() const
{
    return 2.0*sqrt(pow(size.x/2.0f,2.0) + pow(size.y/2.0,2.0));
}
