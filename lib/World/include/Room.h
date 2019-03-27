
#ifndef OOP_ROOM_H
#define OOP_ROOM_H


#include <Door.h>
#include <sstream>


class Room
{
public:

    Room(ID id, const Name& name);

    // Getters
    ID const& getId() const{return id;};
    Name const& getName() const{return name;};
    std::vector<std::string> const& getDescriptions() const{return descriptions;};
    std::vector<std::string> const& getExtendedDescriptions() const{return extendedDescriptions;};
    std::vector<std::string> const& getKeywords() const{return keywords;};
    std::vector<ID> const& getObjectList() const{return objectList;};
    std::vector<Name> const& getUsernameList() const{return usernameList;};
    std::vector<Door> const& getDoorList() const {return doorList;};
    std::vector<Name> const& getCharacterList() const{return characterList;};

    // Adders
    void addDescription(const std::string& description);
    void addExtendedDescription(const std::string& extDescription);
    void addKeywords(const std::string& keyword);

    /*
     * Adder functions
     * Post-condition:
         *          return true if the element is successfully added
         *          return false otherwise
     */
    bool addObject(ID objectId);
    bool addCharacter(const Name &userName);
    bool addDoor(ID doorId, ID designatedRoomId, const std::string& direction);

    /*
     * Remover functions
     * Post-condition:
         *          return true if the element is successfully removed
         *          return false otherwise
     */
    bool removeObject(ID objectId);
    bool removeCharacter(const Name &userName);
    bool removeDoor(ID doorId);


    /*
     * This function return the information of the room including room descriptions and doors information
     * Post-condition:
     *              return: string, information of the room
     */
    std::string getTextOfRoomDetails();

    /*
     * This function return the doors information
     * Post-condition:
     *              return: string, information of all the doors in the room
     */
    std::string getTextOfDoorDetails();

    /*
     * this function returns the Door object according to the door id
     */
    Door* searchDoor(ID doorId);
    Door* searchDoorByDirection(const std::string& direction);

private:
    ID  id;
    std::string name;
    std::vector<std::string> descriptions;
    std::vector<std::string> extendedDescriptions;
    std::vector<std::string> keywords;
    std::vector<ID> objectList;
    std::vector<Name> characterList;
    std::vector<Door> doorList;

    template <typename T>
    bool addUniqueItemToList(T id, std::vector<T> &list);

    template <typename T>
    bool removeUniqueItemFromList(T id, std::vector<T> &list);
};


#endif //OOP_ROOM_H
