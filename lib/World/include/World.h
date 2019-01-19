
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

    //void addObject();

    void writeJson(string filename);
    void readJson(string filename);
private:

    vector<std::unique_ptr<Area>> areas;

    //vector<std::unique_ptr<Entity>> entities;
};
#endif //OOP_WORLD_H
