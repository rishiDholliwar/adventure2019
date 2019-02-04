
#ifndef OOP_ROOM_H
#define OOP_ROOM_H

#include <vector>
#include <string>
#include <memory>
#include <string_view>

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
    std::vector<std::string> const& getUsernameList() const{return usernameList;};

    // Adders
    void addDescription(const std::string& description);
    void addExtendedDescription(const std::string& extDescription);
    bool addCharacter(ID characterId);
    bool addObject(ID objectId);
    bool addUserName(const std::string& userName);

    // Removers
    bool removeCharacter(ID characterId);
    bool removeObject(ID objectId);
    bool removeUserName(const std::string& userName);

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
    std::vector<std::string> usernameList;

    struct LinkingRoomList{
        ID north = 0;
        ID west = 0;
        ID south = 0;
        ID east = 0;
    };

    LinkingRoomList linkingRoomList;

    template <typename T>
    bool addUniqueItemToList(T id, std::vector<T> &list);

    template <typename T>
    bool removeUniqueItemFromList(T id, std::vector<T> &list);
};


#endif //OOP_ROOM_H
