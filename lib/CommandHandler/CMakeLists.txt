add_library(commandHandler
  src/CommandHandler.cpp
  src/CommandTranslator.cpp)

find_package(Boost 1.66 COMPONENTS system REQUIRED)

target_include_directories(commandHandler
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(commandHandler
  PRIVATE
    jsonThingy
    commands
    Character
    controllers
    userController
    world
    Object
    utility
    ${Boost_LIBRARIES}
)

set_target_properties(commandHandler
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

install(TARGETS commandHandler
  ARCHIVE DESTINATION lib
)
