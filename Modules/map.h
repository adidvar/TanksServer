#ifndef MAP_H
#define MAP_H
#include <vector>
#include <string>
#include <memory>

#include <collider.h>

#include "module.h"

class Map : public Module
{
protected:
    std::string maptext;
    std::vector<std::shared_ptr<Collider>> walls;
    std::vector<std::tuple<float , float , int>> spawn_points;

    bool LoadMap(std::string file_name);
public:
    Map(ModuleInterface &interface , std::string file);

    virtual boost::json::object DefaultSettings() const override;
    virtual void LoadSettings(const boost::json::object &obj) override;

    virtual void Start() override;
    virtual void Event(std::any &sign) override;

    const std::vector<std::tuple<float,float,int>>& GetSpawns() const;
    const std::vector<std::shared_ptr<Collider>>& GetWalls() const;
};

struct MapUpdateEvent{
    Map *map;
};

#endif // MAP_H
