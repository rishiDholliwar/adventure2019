#ifndef OOP_ROOM_H
#define OOP_ROOM_H


#include <Door.h>
#include <sstream>
#include "ExtendedDescription.h"


class Room
{
public:

    Room() = default;

    Room(ID id, const Name &name, const std::vector<std::string> &descriptions, const std::vector<Door> &doorList,
         const std::vector<ExtendedDescription> &extendedDescriptions);

    // Getters

    ID const& getId() const{return id;}
    Name const& getName() const{return name;}
    std::vector<std::string> const& getDescriptions() const{return descriptions;}
    std::vector<ExtendedDescription> const& getExtendedDescriptions() const{return extendedDescriptions;}
    const std::vector<Door> &getDoorList() const {return doorList;}


    const std::vector<Name>& getCharacterList() const{return characterList;}
    std::vector<ID> const& getObjectList() const{return objectList;}


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
    void addObject(ID objectId);
    void addCharacter(const Name &userName);
    bool addDoor(ID doorId, ID designatedRoomId, const std::string& direction);
    bool addUserName(const Name &userName);

    /*
     * Remover functions
     * Post-condition:
         *          return true if the element is successfully removed
         *          return false otherwise
     */
    bool removeObject(ID objectId);
    bool removeCharacter(const Name &userName);
    bool removeDoor(ID doorId);
    void removeDoorByDirection(const std::string& direction);


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
    Name name;
    std::vector<std::string> descriptions;
    std::vector<Door> doorList;
    std::vector<ExtendedDescription> extendedDescriptions;

    std::vector<ID> objectList;
    std::vector<Name> characterList;

    template <typename T>
    bool addUniqueItemToList(T id, std::vector<T> &list);

    template <typename T>
    bool removeUniqueItemFromList(T id, std::vector<T> &list);
};


#endif //OOP_ROOM_H
