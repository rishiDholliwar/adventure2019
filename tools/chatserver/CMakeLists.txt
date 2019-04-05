
add_executable(chatserver
  chatserver.cpp
)

set_target_properties(chatserver
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
                      PREFIX ""
)

find_package(Threads REQUIRED)
find_package(Boost 1.66 COMPONENTS system filesystem REQUIRED)

target_link_libraries(chatserver
  PUBLIC
    networking
    jsonThingy
  PRIVATE
    scheduler
    commands
    commandHandler
    userController
    json
    utility
    controllers
    world
    Character
    jsonObjects
    combat
    miniGame
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
)

install(TARGETS chatserver
  RUNTIME DESTINATION bin
)

