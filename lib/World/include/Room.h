
#ifndef OOP_ROOM_H
#define OOP_ROOM_H

#include <vector>
#include <string>
#include <memory>


class Room
{
public:
    Room(int id, const std::string& name);
    void addDescription(const std::string& description);
    void addExtendedDescription(const std::string& extDescription);
    int const& getId() const{return id;};
    std::string const& getName() const{return name;};
    std::vector<std::string> const& getDescriptions() const{return descriptions;};
    std::vector<std::string> const& getExtendedDescriptions() const{return extendedDescriptions;};
    std::vector<int> const& getCharacterList() const{return characterList;};
    std::vector<int> const& getObjectList() const{return objectList;};
    bool addCharacter(int characterId);
    bool removeCharacter(int characterId);
    bool addObject(int objectId);
    bool removeObject(int objectId);

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
};


#endif //OOP_ROOM_H
