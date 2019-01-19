#include <World.h>

World::World() = default;

void World::addArea(std::unique_ptr<Area>& area) {
    World::areas.push_back(std::move(area));
}