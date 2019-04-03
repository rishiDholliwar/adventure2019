#include <ObjectController.h>
#include <algorithm>
#include <Utility.h>

ObjectController::ObjectController(std::vector<Object> objVect) {
	for (auto &obj : objVect) {
		addObjectToList(obj);
	}
}

void ObjectController::addObjectsToList(const std::vector<Object> objs) {
	for (auto &obj : objs) {
		addObjectToList(obj);
	}
}

bool ObjectController::addObjectToList(const Object &object) {
	objects.insert( { object.getID(), object } );
    return true;
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

Object ObjectController::getObjectFromListByJSONObjectID(const ID jsonObjectID) const {
	auto itr = find_if(objects.begin(), objects.end(), [ jsonObjectID ] (std::pair<ID, Object> const& objPair )->bool {
        return objPair.second.getObjectID() == jsonObjectID;
    });
    auto objectID = itr->second.getObjectID();
    auto keywords = itr->second.getKeywords();
    auto shortdesc = itr->second.getShortDesc();
    auto longdesc = itr->second.getLongDesc();
    auto extra = itr->second.getExtra();
    Object newObj(objectID, keywords, shortdesc, longdesc, extra);
    return std::move(newObj);
}

const Object &ObjectController::getObjectFromList(const ID objectID) const {
    return objects.find(objectID)->second;
}

const Object& ObjectController::getObjectFromList(const Name objectName) const {
    auto itr = find_if(objects.begin(), objects.end(), [ objectName ] (std::pair<ID, Object> const& objPair )->bool {
        return objPair.second.getName() == objectName;
    });
    return itr->second;
}

std::string ObjectController::lookItem(Name objectName) {
    auto object = getObjectFromList(objectName);
    std::stringstream ss;
    ss << "\t" << object.getShortDesc() << "\n";
    return ss.str();
}

std::string ObjectController::examineItem(Name objectName) {
    auto object = getObjectFromList(objectName);
    auto extDescriptions = object.getLongDesc();
    if (extDescriptions.empty()){
        return lookItem(objectName);
    }
    return utility::extractStringVector(extDescriptions);
}

std::string ObjectController::lookItem(ID objectID) {
    auto object = getObjectFromList(objectID);
    std::stringstream ss;
    ss << "\t" << object.getShortDesc() << "\n";
    return ss.str();
}

std::string ObjectController::examineItem(ID objectID) {
    auto object = getObjectFromList(objectID);
    auto extDescriptions = object.getLongDesc();
    if (extDescriptions.empty()){
        return lookItem(objectID);
    }
    return utility::extractStringVector(extDescriptions);
}
