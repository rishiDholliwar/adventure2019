
#ifndef OOP_WORLD_H
#define OOP_WORLD_H

#include <vector>
#include <string>
#include "Area.h"
#include <memory>

class World
{
public:
    World();
    void addArea(Area* area);
    std::vector<Area*> const& getArea() const{return areas;};

private:

    std::vector<Area*> areas;

};
#endif //OOP_WORLD_H
