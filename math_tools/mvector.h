#ifndef MVECTOR_H
#define MVECTOR_H
#include "math.h"

struct Vector
{
    Vector(float x , float y):
        x(x) , y(y){}
    Vector():
        x(0.0) , y(0.0){}
    Vector(const Vector&) = default;
    float x;
    float y;
    static Vector fromVector(float forge , float angle );

    float Module() const {return sqrt(pow(x,2) + pow(y,2));}
    Vector Rotate( float angle ) const {return {x*cos(angle) - y*sin(angle) , x*sin(angle) + y*cos(angle)};};
    Vector Nomalize() const {return Vector(x/Module(),y/Module());} // РїРѕРІРµСЂС‚Р°С” СЃРїС–РІРЅР°РїСЂР°РІР»РµРЅРёР№ РІРµРєС‚РѕСЂ РґРѕРІР¶РёРЅРѕСЋ РІ 1
    Vector operator +(const Vector v2) const {return Vector(this->x + v2.x , this->y + v2.y);}
    Vector operator -(const Vector &v2) const {return Vector(this->x - v2.x , this->y - v2.y);}
    Vector operator *(float f) const {return Vector(this->x *f , this->y *f);}
    Vector operator /(float f) const {return Vector(this->x /f , this->y /f);}
};

inline Vector Vector::fromVector(float forge, float angle)
{
    return Vector(forge * cos(angle) , forge * sin(angle) );
}

#endif // MVECTOR_H
