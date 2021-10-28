#include "mvector.h"

Vector Vector::fromVectorAndNormal(Vector direction, Vector normal)
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
