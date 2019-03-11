#include <ObjectController.h>
#include <algorithm>
#include <Utility.h>

ObjectController::ObjectController(){
	//
};

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

std::string ObjectController::lookItem(ID objectID) {
	auto object = getObjectFromList(objectID);
	return utility::lookEntity(object);
}

std::string ObjectController::examineItem(ID objectID) {
	auto object = getObjectFromList(objectID);
	return utility::examineEntity(object);
}