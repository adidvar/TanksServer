#ifndef MVECTOR_H
#define MVECTOR_H
#include <cmath>

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

    float Module() const {return static_cast<float>(sqrt(pow(x,2) + pow(y,2)));}
    Vector Rotate(float angle) const;;
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

inline Vector Vector::Rotate(float angle) const
{
    return { x * static_cast<float>(cos(angle)) - y * static_cast<float>(sin(angle)) , x * static_cast<float>(sin(angle)) + y * static_cast<float>(cos(angle)) }; 
}

#endif // MVECTOR_H
