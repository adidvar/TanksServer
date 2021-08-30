#ifndef COLLISION_H
#define COLLISION_H

#include <vector>
#include "shapes.h"
#include "object.h"

class Object;

[[deprecated]]
void ExecuteCollision(Object *obj1 , Object *obj2);

Vector generate_normal(Line line);

bool lines_collision(Line l1 , Line l2 , Vector &collision);



#endif // COLLISION_H
