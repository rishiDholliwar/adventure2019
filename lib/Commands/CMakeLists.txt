add_library(commands
  src/Command.cpp
  src/GameCommands.cpp
  src/UserCommands.cpp)

find_package(Boost 1.66 COMPONENTS system REQUIRED)

target_include_directories(commands
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(commands
  PRIVATE
    commandHandler
    networking
    gameController
    userController
    controllers
    utility
    ${Boost_LIBRARIES}
)

set_target_properties(commands
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

install(TARGETS commands
  ARCHIVE DESTINATION lib
)
