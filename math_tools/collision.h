#ifndef COLLISION_MATH_H
#define COLLISION_MATH_H

#include "mvector.h"
#include <vector>

struct line
{
    Vector begin;
    Vector end;
};

class PointShape
{
    std::vector<Vector> points;
    bool convexity; // напрямок роботи даної колізії (внутрішня в середину) (зовнішня навпаки випихає)
};

class MultiPointShape
{
   std::vector<PointShape> shapes;

    //ОПЕРАТОРИ ПЕРЕТИНУ
};

Vector generate_normal(line line);

bool lines_collision(line l1 , line l2 , Vector &collision);

#endif // COLLISION_MATH_H
