add_library(scheduler
  src/Scheduler.cpp)

find_package(Boost 1.66 COMPONENTS system REQUIRED)

target_include_directories(scheduler
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(scheduler
  PRIVATE
    networking
    commands
    utility
    controllers
    Character
    world
    Object
    ${Boost_LIBRARIES}
)

set_target_properties(scheduler
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

install(TARGETS scheduler
  ARCHIVE DESTINATION lib
)
