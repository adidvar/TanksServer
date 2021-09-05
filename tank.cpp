#include "tank.h"
#include "debug_tools/out.h"

#include <math.h>

const float move_speed = +0.02;
const float rotation_speed = 0.03;
const float tower_speed = 0.02;

Tank::Tank(ObjectInterface *interface, std::string name, int health_max):
    Object(interface, {0,0} , {2,1} ,0 , true),
    name(name),
    health(health_max),
    health_max(health_max)
{
}

void Tank::Update()
{
    position = position + Vector::fromVector(controller.position_direction * move_speed , rotate);
    rotate += controller.angle_direction * rotation_speed;
    tower_angle += controller.tower_angle_direction * tower_speed + controller.angle_direction * rotation_speed;
}

void Tank::SetMove(int move, int rotation, int tower_rotation)
{
    this->controller.position_direction = move;
    this->controller.angle_direction = rotation;
    this->controller.tower_angle_direction = tower_rotation;
}

void Tank::Fire()
{
   // auto bullet = new Bullet(30 , this->position , Vector2f::fromVector(1,sin(tower_angle),cos(tower_angle)), 0.1);
    // this->register_bullet(bullet);
}

void Tank::Collision(Object *obj, Vector normal)
{
    info("Collision");
    position = position+ normal*(move_speed);
}

MultiPointShape Tank::Poligon() const
{
   auto objects = Object::Poligon();
   return objects;
}

void Tank::Spawn(Vector position, size_t team_id)
{
    this->position = position;
    this->team_id = team_id;
    this->health = health_max;
}
/*
void Tank::Collision(map_rect *rect, Vector normal)
{
    info("Coll");
    position = position+ normal*(-move_speed);
}

void Tank::Collision(shared_ptr<Tank>, Vector2f normal)
{
    if(this->position_direction != 0)
        position = position+ normal*(-move_speed);
}

void Tank::Collision(shared_ptr<Bullet>, Vector2f normal)
{

}
*/

void Tank::Damage(unsigned damage)
{
    health -= damage;
}
