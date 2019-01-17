
#ifndef OOP_WORLD_H
#define OOP_WORLD_H

#include <iostream>
#include <vector>
#include <string>
#include <Area.h>

using namespace std;

class World
{
public:
    World();
private:
    vector<Area> areas;
};
#endif //OOP_WORLD_H
