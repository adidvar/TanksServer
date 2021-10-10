#ifndef MAP_H
#define MAP_H
#include <vector>
#include <string>
#include <memory>

#include <archive.h>
#include <collider.h>

#include "module.h"

class Map : public Module
{
protected:
    std::string maptext;
    std::vector<std::shared_ptr<Collider>> walls;
public:
    Map(ModuleInterface &interface , std::string file);

    virtual void Start() override;
    virtual void Signal(GameSignal sign) override;
    void write(archive &arc);
};

#endif // MAP_H
