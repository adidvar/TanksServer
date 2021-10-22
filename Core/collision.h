#ifndef COLLISION_H
#define COLLISION_H

#include "shapes.h"
#include "object.h"

class Object;

[[deprecated]]
bool ExecuteCollision(Object *obj1 , Object *obj2);
bool GetCollisions(const MultiPointShape& , const MultiPointShape& , std::vector<Vector>& , std::vector<Vector>&);

Vector generate_normal(Line line);

bool lines_collision(Line l1 , Line l2 , Vector &collision);



#endif // COLLISION_H
