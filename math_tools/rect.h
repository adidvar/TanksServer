#ifndef RECT_H
#define RECT_H

#include <vector>
#include "vector2f.h"

class rect
{
public:
    Vector2f position;
    Vector2f size;
    float rotate;
    std::vector<line> Split() const;
    float Radius() const;
};

#endif // RECT_H
