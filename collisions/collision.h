#ifndef COLLISION_H
#define COLLISION_H

#include "../math/shapes.h"
#include "../objects/object.h"

class Object;

[[deprecated]]
bool ExecuteCollision(Object *obj1 , Object *obj2);

Vector generate_normal(Line line);

bool lines_collision(Line l1 , Line l2 , Vector &collision);



#endif // COLLISION_H
