
#ifndef OOP_WORLD_H
#define OOP_WORLD_H

#include <vector>
#include <string>
#include <Area.h>
#include <memory>

class World
{
public:
    World();
    void addArea(std::unique_ptr<Area> area);
    const std::vector<std::unique_ptr<Area>>& getDoors(){return areas;};
    //void addObject();

    void writeJson(std::string filename);
    void readJson(std::string filename);
private:

    std::vector<std::unique_ptr<Area>> areas;

    //vector<std::unique_ptr<Entity>> entities;
};
#endif //OOP_WORLD_H
