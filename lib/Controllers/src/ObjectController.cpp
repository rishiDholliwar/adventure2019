#include <ObjectController.h>
#include <algorithm>

ObjectController::ObjectController(std::vector<Object> objVect) {
	for (auto &obj : objVect) {
		addObjectToList(obj);
	}
}

bool ObjectController::addObjectToList(const Object &object) {
	objects.insert( { object.getID(), object } );
}

bool ObjectController::doesObjectExist(const ID objectID) {
    return objects.find(objectID) != objects.end();
}

bool ObjectController::doesObjectOfThisNameExist(const Name objectName) {
	auto itr = find_if(objects.begin(), objects.end(), [ objectName ] (std::pair<ID, Object> const& objPair )->bool {
		return objPair.second.getName() == objectName;
	});

	return itr != objects.end();
}

const Object &ObjectController::getObjectFromList(const ID objectID) const {
    return objects.find(objectID)->second;
}
