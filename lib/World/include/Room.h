
#ifndef OOP_ROOM_H
#define OOP_ROOM_H


#include <Door.h>


class Room
{
public:

    Room(ID id, const Name& name);

    // Getters
    ID const& getId() const{return id;};
    Name const& getName() const{return name;};
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
    bool addUserName(const Name& userName);
    bool addDoor(ID doorId, ID designatedRoomId, const std::string& direction);

    /*
     * Remover functions
     * Post-condition:
         *          return true if the element is successfully removed
         *          return false otherwise
     */
    bool removeCharacter(ID characterId);
    bool removeObject(ID objectId);
    bool removeUserName(const std::string& userName);
    bool removeDoor(ID doorId);


    /*
     * This function return the information of the room including room descriptions and doors information
     * Post-condition:
     *              return: string, information of the room
     */
    std::string const getTextOfRoomDetails();

    /*
     * This function return the doors information
     * Post-condition:
     *              return: string, information of all the doors in the room
     */
    std::string const getTextOfDoorDetails();

    /*
     * this function returns the Door object according to the door id
     */
    Door* searchDoor(ID doorId);

private:
    ID  id;
    std::string name;
    std::vector<std::string> descriptions;
    std::vector<std::string> extendedDescriptions;
    std::vector<ID> characterList;
    std::vector<ID> objectList;
    std::vector<std::string> usernameList;
    std::vector<Door> doorList;

    template <typename T>
    bool addUniqueItemToList(T id, std::vector<T> &list);

    template <typename T>
    bool removeUniqueItemFromList(T id, std::vector<T> &list);
};


#endif //OOP_ROOM_H
