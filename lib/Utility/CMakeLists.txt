
add_library(utility
        src/Utility.cpp
        include/Utility.h
        include/AlterSpace.h
        include/JSONUser.h
        include/JSONObjects.h
        )

add_library(returnCode
        include/Response.h
        include/ReturnCodes.h)

add_library(uniqueID
          src/UniqueID.cpp)

add_library(stringModifier
        src/stringModifier.cpp)

add_library(jsonUser
        include/JSONUser.h )

add_library(jsonObjects
        include/JSONObjects.h)

target_include_directories(utility
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${Boost_INCLUDE_DIR}
        )

target_include_directories(returnCode
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${Boost_INCLUDE_DIR}
        )

target_include_directories(jsonUser
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${Boost_INCLUDE_DIR}
        )

target_include_directories(jsonObjects
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${Boost_INCLUDE_DIR}
        )

target_link_libraries(jsonUser
        json
        userController
        ${Boost_LIBRARIES}
        )

target_link_libraries(jsonObjects
        json
        Object
        )

target_link_libraries(returnCode
    PUBLIC
        networking
        )

target_include_directories(uniqueID
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    utility
    ${Boost_INCLUDE_DIR}
)

target_include_directories(stringModifier
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${Boost_INCLUDE_DIR}
)

set_target_properties(utility
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 17
        )

set_target_properties(returnCode
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 17
        )

set_target_properties(jsonUser
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 17
        )

set_target_properties(jsonObjects
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 17
        )

set_target_properties(uniqueID
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

set_target_properties(stringModifier
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

install(TARGETS utility
        ARCHIVE DESTINATION lib
)

install(TARGETS returnCode
  ARCHIVE DESTINATION lib
)

install(TARGETS uniqueID
  ARCHIVE DESTINATION lib
)

install(TARGETS stringModifier
  ARCHIVE DESTINATION lib
)

install(TARGETS jsonUser
        ARCHIVE DESTINATION lib
)

install(TARGETS jsonObjects
        ARCHIVE DESTINATION lib
)
