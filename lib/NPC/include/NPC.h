#ifndef ALTERSPACE_NPC_H
#define ALTERSPACE_NPC_H

#include <string>
#include <vector>
#include <AlterSpace.h>
#include <UniqueID.h>
#include <utility>

using AlterSpace::ID;
using AlterSpace::Name;

class NPC : public UniqueID {
private:
    Name name;
    ID roomID;

    std::vector<std::string> descriptions;
    std::vector<std::string> extendedDescriptions;

public:
    NPC(const Name &name, ID roomID);
    Name getName() const;
    ID getRoomID() const;
    ID getID() const;
    std::string getInfo() const;

    void setRoomID(ID roomID);

    std::vector<std::string> const& getDescriptions() const{return descriptions;};
    std::vector<std::string> const& getExtendedDescriptions() const{return extendedDescriptions;};

    // look and examine
    std::string look();
    std::string examine();
};


#endif //ALTERSPACE_NPC_H
