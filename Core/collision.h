#ifndef COLLISION_H
#define COLLISION_H

#include "shapes.h"
#include "object.h"

class Object;

[[deprecated]]
bool ExecuteCollision(Object *obj1 , Object *obj2);
bool GetCollisions(const std::vector<Line> &lines1 , const std::vector<Line> &lines2 , std::vector<Vector>& , std::vector<Vector>&);

Vector generate_normal(Line line);

bool lines_collision(Line l1 , Line l2 , Vector &collision);

Vector NormalBlocking(Vector direction , Vector normal);



#endif // COLLISION_H
