#ifndef ALTERSPACE_NPC_H
#define ALTERSPACE_NPC_H

#include <string>
#include <vector>
#include <AlterSpace.h>
#include <UniqueID.h>
#include <Object.h>
#include <utility>

using AlterSpace::ID;
using AlterSpace::Name;

class NPC : public UniqueID {
private:
    Name name;
    ID roomID;

public:
    NPC(const Name &name, ID roomID);
    Name getName() const;
    ID getRoomID() const;
    ID getID() const;
    std::string getInfo() const;

    void setRoomID(ID roomID);


    // look and examine
    std::string look();
    std::string examine();
};


#endif //ALTERSPACE_NPC_H
