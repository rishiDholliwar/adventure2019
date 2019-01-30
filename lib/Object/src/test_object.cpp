//
// Created on 1/22/2019.
//

#include <stdio.h>
#include <iostream>
#include "../include/Object.h"

int main(int argc, char** argv){

    std::string testObjectName = "object01";
    std::string testObjectID = "objectID01";
    std::string testObjectShortDesc = "Short description";
    std::string testObjectLongDesc = "Long description";
    
    Object obj(testObjectID,testObjectName,testObjectShortDesc,testObjectLongDesc);
    obj.printTest();
    return 0;
}