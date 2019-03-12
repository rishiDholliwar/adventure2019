
add_library(userController
  src/User.cpp
  src/UserController.cpp)

find_package(Boost 1.66 COMPONENTS system REQUIRED)

target_include_directories(userController
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(userController
  PUBLIC
    networking
    returnCode
    jsonUser
  PRIVATE
    ${Boost_LIBRARIES}
)

set_target_properties(userController
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

install(TARGETS userController
  ARCHIVE DESTINATION lib
)
