#ifndef COLLISION_MATH_H
#define COLLISION_MATH_H

#include "vector2f.h"

Vector2f generate_normal(line line);

bool lines_collision(line l1 , line l2 , Vector2f & collision);

#endif // COLLISION_MATH_H
