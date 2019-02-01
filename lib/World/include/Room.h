
#ifndef OOP_ROOM_H
#define OOP_ROOM_H

#include <vector>
#include <string>
#include <memory>


class Room
{
public:
    Room(int id, const std::string& name);

    // Getters
    int const& getId() const{return id;};
    std::string const& getName() const{return name;};
    std::vector<std::string> const& getDescriptions() const{return descriptions;};
    std::vector<std::string> const& getExtendedDescriptions() const{return extendedDescriptions;};
    std::vector<int> const& getCharacterList() const{return characterList;};
    std::vector<int> const& getObjectList() const{return objectList;};

    // Adders
    void addDescription(const std::string& description);
    void addExtendedDescription(const std::string& extDescription);
    bool addCharacter(int characterId);
    bool addObject(int objectId);

    // Removers
    bool removeCharacter(int characterId);
    bool removeObject(int objectId);

    // Link Rooms
    // use character 'n','e','s','w' to represent direction

    // linkRoom will assign targetRoom to the coordinate Room*
    void linkRoom(char dir, int targetRoomId);
    // return 0 indicates no room is linked in the direction
    int getLinkedRoom(char dir);


private:
    int  id;
    std::string name;
    std::vector<std::string> descriptions;
    std::vector<std::string> extendedDescriptions;
    std::vector<int> characterList;
    std::vector<int> objectList;
    int north;
    int east;
    int south;
    int west;
    bool addIdToList(int id, std::vector<int> &list);
    bool removeIdFromList(int id, std::vector<int> &list);
};


#endif //OOP_ROOM_H
