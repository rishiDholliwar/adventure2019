#include <World.h>

World::World() {

}

void World::addArea(Area &area) {
    World::areas.push_back(area);
}