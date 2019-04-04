#ifndef UNIQUE_H
#define UNIQUE_H

#include <AlterSpace.h>

using AlterSpace::ID;

class UniqueID {
private:
	static int nextID;
protected:
   ID id;
public:
   UniqueID();
   // UniqueID(const UniqueID& orig);
   // UniqueID& operator=(const UniqueID& orig);
};

#endif
