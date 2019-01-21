
add_library(worldManager
  src/WorldManager.cpp)

find_package(Boost 1.66 COMPONENTS system REQUIRED)

target_include_directories(worldManager
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(worldManager
  PUBLIC
    userManager
    utility
  PRIVATE
    ${Boost_LIBRARIES}
)

set_target_properties(worldManager
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

install(TARGETS worldManager
  ARCHIVE DESTINATION lib
)
