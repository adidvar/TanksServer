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
    [[deprecated]]
    static Vector fromVector(float forge , float cos, float sin );

    float Module() const {return sqrt(pow(x,2) + pow(y,2));}
    Vector Rotate( float sin , float cos) {return {x*cos - y*sin , x*sin + y*cos};};
    Vector Nomalize() const {return Vector(x/Module(),y/Module());} // РїРѕРІРµСЂС‚Р°С” СЃРїС–РІРЅР°РїСЂР°РІР»РµРЅРёР№ РІРµРєС‚РѕСЂ РґРѕРІР¶РёРЅРѕСЋ РІ 1
    Vector operator +(Vector v2){return Vector(this->x + v2.x , this->y + v2.y);}
    Vector operator -(Vector &v2){return Vector(this->x - v2.x , this->y - v2.y);}
    Vector operator *(float f){return Vector(this->x *f , this->y *f);}
    Vector operator /(float f){return Vector(this->x /f , this->y /f);}
};

inline Vector Vector::fromVector(float forge, float cos, float sin)
{
    return Vector(forge * cos , forge * sin );
}

#endif // MVECTOR_H
