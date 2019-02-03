
#ifndef OOP_ROOM_H
#define OOP_ROOM_H

#include <vector>
#include <string>
#include <memory>

using ID = unsigned int;

enum class Direction{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

class Room
{
public:

    Room(ID id, const std::string& name);

    // Getters
    ID const& getId() const{return id;};
    std::string const& getName() const{return name;};
    std::vector<std::string> const& getDescriptions() const{return descriptions;};
    std::vector<std::string> const& getExtendedDescriptions() const{return extendedDescriptions;};
    std::vector<ID> const& getCharacterList() const{return characterList;};
    std::vector<ID> const& getObjectList() const{return objectList;};

    // Adders
    void addDescription(const std::string& description);
    void addExtendedDescription(const std::string& extDescription);
    bool addCharacter(ID characterId);
    bool addObject(ID objectId);

    // Removers
    bool removeCharacter(ID characterId);
    bool removeObject(ID objectId);

    // Link Rooms
    // use character 'n','e','s','w' to represent direction

    // linkRoom will assign targetRoom to the coordinate Room*
    void linkRoom(Direction dir, ID targetRoomId);
    // return 0 indicates no room is linked in the direction
    ID getLinkedRoom(Direction dir);


    bool hasObject(ID objectId);

private:
    ID  id;
    std::string name;
    std::vector<std::string> descriptions;
    std::vector<std::string> extendedDescriptions;
    std::vector<ID> characterList;
    std::vector<ID> objectList;

    struct LinkingRoomList{
        ID north = 0;
        ID west = 0;
        ID south = 0;
        ID east = 0;
    };

    LinkingRoomList linkingRoomList;
    bool addIdToList(ID id, std::vector<ID> &list);
    bool removeIdFromList(ID id, std::vector<ID> &list);
};


#endif //OOP_ROOM_H
