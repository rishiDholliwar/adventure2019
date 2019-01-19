#include <World.h>

World::World() {

}

void World::addArea(std::unique_ptr<Area> area) {
    World::areas.push_back(area);
}