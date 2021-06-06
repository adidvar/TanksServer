#include "math_tools/collision.h"
#include "math.h"

bool in_range(float m1 , float m2 , float value)
{
    return (std::min(m1,m2) < value && value < std::max(m1,m2) );
}

Vector2f generate_normal(line line)
{
    Vector2f pos = {line.end.x - line.begin.x , line.end.y - line.begin.y};
    return Vector2f{ -pos.y , pos.x};
}

bool cross(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4 , float &x , float &y) {
    float n;
    if (y2 - y1 != 0) {  // a(y)
        float q = (x2 - x1) / (y1 - y2);
        float sn = (x3 - x4) + (y3 - y4) * q; if (!sn) { return 0; }  // c(x) + c(y)*q
        float fn = (x3 - x1) + (y3 - y1) * q;   // b(x) + b(y)*q
        n = fn / sn;
    }
    else {
        if (!(y3 - y4)) { return 0; }  // b(y)
        n = (y3 - y1) / (y3 - y4);   // c(y)/b(y)
    }
    x = x3 + (x4 - x3) * n;  // x3 + (-b(x))*n
    y = y3 + (y4 - y3) * n;  // y3 +(-b(y))*n
    return 1;
}


bool lines_collision(line l1 , line l2 , Vector2f & collision)
{
    float x , y;

    bool result = cross(l1.begin.x,l1.begin.y,l1.end.x ,l1.end.y , l2.begin.x ,l2 .begin.y , l2.end.x , l2.end.y , x , y);
    collision = {x,y};
    if(result == false)
        return false;
    else
    {
        if(in_range(l1.begin.x , l1.end.x , x) &&
           in_range(l1.begin.y , l1.end.y , x) &&
           in_range(l2.begin.x , l2.end.x , x) /* &&
           in_range(l2.begin.y , l2.end.y , y)
               */ )
            return true;
        else
            return false;
    }
}

