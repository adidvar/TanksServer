#ifndef OBJECTINTERFACE_H
#define OBJECTINTERFACE_H

#include <memory>
#include <string>
#include <functional>

class Object;
class Bullet;
class Game;

class ObjectInterface
{
    std::function<void(std::shared_ptr<Bullet>)> spawnbullet;

    friend class Game;
public:
    ObjectInterface();
//    void Notificate(Object* , std::string);
    void SpawnBullet(std::shared_ptr<Bullet> bullet);
};

#endif // OBJECTINTERFACE_H
