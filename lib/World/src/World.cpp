#include <World.h>

World::World() = default;

void World::addArea(Area* area) {
    World::areas.push_back(area);
}