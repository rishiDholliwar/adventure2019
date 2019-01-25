
add_library(gameController
  src/GameController.cpp)

find_package(Boost 1.66 COMPONENTS system REQUIRED)

target_include_directories(gameController
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(gameController
  PUBLIC
    userManager
    utility
  PRIVATE
    ${Boost_LIBRARIES}
)

set_target_properties(gameController
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

install(TARGETS gameController
  ARCHIVE DESTINATION lib
)