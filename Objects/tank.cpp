#include "tank.h"

#include <cmath>
#include <out.h>

#include "collider.h"
#include "bullet.h"
#include "collision.h"

float Tank::move_speed = +0.00125f;
float Tank::rotation_speed = 0.0015f;
float Tank::tower_speed = 0.001f;
const float tower_len = 2.4f;

Tank::Tank(ObjectInterface &interface, std::string name, int health_max):
    Object(interface, {0,0} , {2,1} ,0 , true),
    name(name),
    health(health_max),
    health_max(health_max)
{
}

void Tank::Update(unsigned delta_time)
{
    speed = Vector::fromVector(controller.position_direction * move_speed * delta_time, rotate);
    position = position + col_speed;
    rotate += controller.angle_direction * rotation_speed * delta_time;
    tower_angle += controller.tower_angle_direction * tower_speed * delta_time /*+ controller.angle_direction * rotation_speed*/;
}

void Tank::SetMove(int move, int rotation, int tower_rotation)
{
    this->controller.position_direction = move;
    this->controller.angle_direction = rotation;
    this->controller.tower_angle_direction = tower_rotation;
}

void Tank::Fire()
{
    auto bullet = new Bullet(this->interface , this->position + Vector::fromVector(tower_len , tower_angle) , this->team_id , this->tower_angle , 60);
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

void Tank::CollisionCycleBegin(unsigned delta_time)
{
    this->col_speed = speed;
}

void Tank::CollisionCycleEnd(unsigned delta_time)
{

}

void Tank::CollisionEvent(Object *obj, Vector normal , unsigned delta_time)
{
    if (dynamic_cast<Collider*>(obj) != nullptr)
    {
        this->col_speed = NormalBlocking(col_speed,normal);
        if(this->controller.angle_direction !=0)
            position = position + normal *	 (move_speed) * delta_time;
    }
    if (dynamic_cast<Tank*>(obj) != nullptr)
    {
        if(this->controller.position_direction !=0)
            position = position + normal * (move_speed) * delta_time;
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
