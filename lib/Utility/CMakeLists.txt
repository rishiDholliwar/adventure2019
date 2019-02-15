
add_library(utility
        src/Utility.cpp
        include/Utility.h
        include/AlterSpace.h
        include/JSONUser.h
        )

add_library(returnCode
        include/Response.h
        include/ReturnCodes.h)

add_library(jsonUser
        include/JSONUser.h)

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

target_link_libraries(jsonUser
        json
        userController
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

install(TARGETS utility
  ARCHIVE DESTINATION lib
)

install(TARGETS returnCode
  ARCHIVE DESTINATION lib
)

install(TARGETS jsonUser
  ARCHIVE DESTINATION lib
)