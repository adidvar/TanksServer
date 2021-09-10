#ifndef SHAPES_H
#define SHAPES_H

#define _USE_MATH_DEFINES
#include <cmath>
#include "mvector.h"
#include <vector>
#include <iterator>

struct Line
{
    Vector begin;
    Vector end;
    Vector normal;
};

class PointShape
{
public:
    std::vector<Vector> points;
    bool convexity = true; // напрямок роботи даної колізії (внутрішня в середину) (зовнішня навпаки випихає)
public:
    void ToLines(std::back_insert_iterator<std::vector<Line>> inserter) const;
};

class MultiPointShape
{
public:
   std::vector<PointShape> shapes;
public:
   void ToLines(std::back_insert_iterator<std::vector<Line>> inserter) const;
   //ОПЕРАТОРИ ПЕРЕТИНУ
};

#endif // COLLISION_MATH_H
