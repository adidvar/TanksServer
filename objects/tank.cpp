#include "tank.h"

#include <cmath>
#include <out.h>

#include "collider.h"
#include "bullet.h"

float Tank::move_speed = +0.025f;
float Tank::rotation_speed = 0.03f;
float Tank::tower_speed = 0.02f;

Tank::Tank(ObjectInterface &interface, std::string name, int health_max):
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
    tower_angle += controller.tower_angle_direction * tower_speed /*+ controller.angle_direction * rotation_speed*/;
}

void Tank::SetMove(int move, int rotation, int tower_rotation)
{
    this->controller.position_direction = move;
    this->controller.angle_direction = rotation;
    this->controller.tower_angle_direction = tower_rotation;
}

void Tank::Fire()
{
    auto bullet = new Bullet(this->interface , this->position , this->team_id , this->tower_angle , 60);
    interface.SpawnBullet( std::shared_ptr<Bullet>(bullet) );
}

size_t Tank::Team()
{
    return team_id;
}

bool Tank::IsLive()
{
    return health > 0;
}

void Tank::Collision(Object *obj, Vector normal)
{
    if (dynamic_cast<Collider*>(obj) != nullptr)
    {
        info("Collision");
        position = position + normal * (move_speed);
    }
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
