#include "collision.h"
#include <cmath>
#include <cassert>

bool in_range(float m1 , float m2 , float value)
{
    if(m1 == m2 && m1==value)
        return true;
    return (std::min(m1,m2) <= value && value <= std::max(m1,m2) );
}
/*
Vector generate_normal(Line line)
{
    Vector pos = {line.end.x - line.begin.x , line.end.y - line.begin.y};
    return Vector{ -pos.y , pos.x};
}
*/

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


bool lines_collision(Line l1 , Line l2 , Vector & collision)
{
    float x = 0 , y = 0;

    bool result = cross(l1.begin.x,l1.begin.y,l1.end.x ,l1.end.y , l2.begin.x ,l2 .begin.y , l2.end.x , l2.end.y , x , y);
    collision = {x,y};
    if(result == false)
        return false;
    else
    {
        if(in_range(l1.begin.x , l1.end.x , x) &&
           in_range(l1.begin.y , l1.end.y , y) &&
           in_range(l2.begin.x , l2.end.x , x)  &&
           in_range(l2.begin.y , l2.end.y , y)
                )
            return true;
        else
            return false;
    }
}
/*

std::vector<line> Split() const
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
float ColisionMaxDistance() const
{
    return 2.0*sqrt(pow(size.x/2.0f,2.0) + pow(size.y/2.0f,2.0));
}
*/
/*
bool ExecuteCollision(Object *obj1, Object *obj2)
{
    std::vector<Line> lines1;
    std::vector<Line> lines2;
    {
        MultiPointShape shape1 = obj1->Poligon();
        MultiPointShape shape2 = obj2->Poligon();
        shape1.ToLines(std::back_inserter(lines1));
        shape2.ToLines(std::back_inserter(lines2));
    }

    Vector v1 {0,0}, v2 {0,0};

    bool col = false;

    for(Line x1 : lines1)
    {
        for(Line x2 : lines2)
        {
            Vector position;
            bool result = lines_collision(x1,x2,position);
            if(result)
            {
                col = true;
                v1= v1+ x2.normal;
                v2= v2+ x1.normal;
            }
        }
    }
    if(col)
    {
        if(obj1->Active())
            obj1->Collision(obj2 , v1);
        if(obj2->Active())
            obj2->Collision(obj1 , v2);
    }
    return col;
}
*/



bool GetCollisions(const std::vector<Line>& lines1, const std::vector<Line> &lines2, std::vector<Vector> &n1, std::vector<Vector> &n2)
{
    bool col = false;

    for(Line x1 : lines1)
    {
        for(Line x2 : lines2)
        {
            Vector position;
            bool result = lines_collision(x1,x2,position);
            if(result)
            {
                col = true;
                n1.push_back(x2.normal);
                n2.push_back(x1.normal);
            }
        }
    }
    return col;
}

Vector NormalBlocking(Vector direction , Vector normal)
{
    if(normal.x == 0 && normal.y == 0)
        return direction;

    float multiplication = direction.x*normal.x + direction.y*normal.y;
    float normal_len = sqrt(normal.x*normal.x + normal.y*normal.y);
    float proection = multiplication / normal_len;

    if(proection > 0)
        return direction;

    Vector proection_vect = {proection* normal.x / normal_len , proection* normal.y / normal_len};

    return {
            direction.x - proection_vect.x
           ,direction.y - proection_vect.y
           };
}
