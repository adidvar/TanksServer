#ifndef MAP_H
#define MAP_H
#include <vector>
#include <string>
#include <memory>

#include "net/archive.h"
#include "object.h"
#include "container.h"
#include "module.h"


class Decor : public Object
{
protected:
    std::string texture;
    friend class Map;
public:
    Decor();
    Decor(Vector position , Vector size , float rotation);
};

class Map : public Module
{
protected:
    std::vector<std::shared_ptr<Decor>> walls;
    std::vector<Decor> backgrounds;
public:
    Map(ModuleInterface &interface , std::string file);

    virtual void Start() override;
    void write(archive &arc);
};

#endif // MAP_H
