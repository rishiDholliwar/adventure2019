
#ifndef OOP_WORLD_H
#define OOP_WORLD_H

#include <vector>
#include <string>
#include <Area.h>

using namespace std;

class World
{
public:
    World();
    void addArea(Area& area);

    //void addObject();

    void writeJson(string filename);
    void readJson(string filename);
private:

    vector<Area> areas;

    //vector<Entity> entities;
};
#endif //OOP_WORLD_H
