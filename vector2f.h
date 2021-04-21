#ifndef VECTOR2F_H
#define VECTOR2F_H
#include "math.h"

struct Vector2f
{
    Vector2f(float x , float y):
        x(x) , y(y){}
    Vector2f():
        x(0.0) , y(0.0){}
    Vector2f(const Vector2f&) = default;
    float x;
    float y;
    static Vector2f fromVector(float forge , float cos, float sin );

    float Module() const {return sqrt(pow(x,2) + pow(y,2));}
    Vector2f Nomalize() const {return Vector2f(x/Module(),y/Module());} // повертає співнаправлений вектор довжиною в 1
    Vector2f operator +(Vector2f v2){return Vector2f(this->x + v2.x , this->y + v2.y);}
    Vector2f operator -(Vector2f &v2){return Vector2f(this->x - v2.x , this->y - v2.y);}
    Vector2f operator *(float f){return Vector2f(this->x *f , this->y *f);}
    Vector2f operator /(float f){return Vector2f(this->x /f , this->y /f);}
};

inline Vector2f Vector2f::fromVector(float forge, float cos, float sin)
{
    return Vector2f(forge * cos , forge * sin );
}

#endif // VECTOR2F_H
