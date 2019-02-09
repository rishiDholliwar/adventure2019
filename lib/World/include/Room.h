
#ifndef OOP_ROOM_H
#define OOP_ROOM_H

#include <string_view>
#include <Door.h>


class Room
{
public:
    using ID = Door::ID;

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

    /*
     * Adder functions
     * Post-condition:
         *          return true if the element is successfully added
         *          return false otherwise
     */
    bool addCharacter(ID characterId);
    bool addObject(ID objectId);
    bool addUserName(const std::string& userName);

    /*
     * Remover functions
     * Post-condition:
         *          return true if the element is successfully removed
         *          return false otherwise
     */
    bool removeCharacter(ID characterId);
    bool removeObject(ID objectId);
    bool removeUserName(const std::string& userName);

    // Link Rooms
    bool addDoor(ID doorId, ID destinatedRoomId, const std::string& direction);
    bool removeDoor(ID doorId);
    std::string const getTextOfRoomDetails();
    std::string const getTextOfDoorDetails();
    ID const& getDestinatedRoomId(ID doorId);

private:
    ID  id;
    std::string name;
    std::vector<std::string> descriptions;
    std::vector<std::string> extendedDescriptions;
    std::vector<ID> characterList;
    std::vector<ID> objectList;
    std::vector<std::string> usernameList;
    std::vector<Door> doorList;

    ID unfoundDoorId = 0;

    template <typename T>
    bool addUniqueItemToList(T id, std::vector<T> &list);

    template <typename T>
    bool removeUniqueItemFromList(T id, std::vector<T> &list);
};


#endif //OOP_ROOM_H
