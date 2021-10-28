#include "objectinterface.h"

ObjectInterface::ObjectInterface()
{
}

void ObjectInterface::SpawnBullet(std::shared_ptr<Bullet> bullet)
{
	spawnbullet(bullet);
}
