#ifndef COLLISION_UP_H
#define COLLISION_UP_H

#include <memory>
#include <vector>

#include "math_tools/collision.h"

using namespace std;

template <typename T1 , typename T2>
void collision( T1 obj1 , T2 obj2)
{
    if(obj1->Radius()+obj2->Radius() <= (obj1->position - obj2->position).Module() )
        return;


    std::vector<line> l1 = obj1->Split();
    std::vector<line> l2 = obj2->Split();

    Vector2f v1 {0,0}, v2 {0,0};

    bool col = false;

    for( line x1 : l1)
    {
        for(line x2 : l2)
        {
            Vector2f position;
            bool result = lines_collision(x1,x2,position);
            if(result)
            {
                col = true;
                v1= v1+ generate_normal(x2).Nomalize();
                v2= v2+ generate_normal(x1).Nomalize();
            }
        }
    }
    if(col)
    {
        obj1->Collision(obj2 , v1);
        obj2->Collision(obj1 , v2);
    }
}


#endif // COLLISION_UP_H
