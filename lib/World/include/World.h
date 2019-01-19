
#ifndef OOP_WORLD_H
#define OOP_WORLD_H

#include <vector>
#include <string>
#include <Area.h>
#include <memory>

struct AreaDeleter {
    void operator()(Area* area);
};

class World
{
public:
    World();
    void addArea(std::unique_ptr<Area,AreaDeleter> area);
    const std::vector<std::unique_ptr<Area,AreaDeleter>>& getDoors(){return areas;};
    //void addObject();

    void writeJson(std::string filename);
    void readJson(std::string filename);
private:

    std::vector<std::unique_ptr<Area,AreaDeleter>> areas;

    //vector<std::unique_ptr<Entity>> entities;
};
#endif //OOP_WORLD_H
