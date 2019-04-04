#include <UniqueID.h>
#include <iostream>

int UniqueID::nextID = 0;

UniqueID::UniqueID() {
   id = ++nextID;
}

// UniqueID::UniqueID(int ID) {
//    id = ID;
// }

// UniqueID::UniqueID(const UniqueID& orig) {
//    id = orig.id;
// }

// UniqueID& UniqueID::operator=(const UniqueID& orig) {
//    id = orig.id;
//    return(*this);
// }
