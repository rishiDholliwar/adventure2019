
add_library(messageDispatcher
  src/MessageDispatcher.cpp)

find_package(Boost 1.66 COMPONENTS system REQUIRED)

target_include_directories(messageDispatcher
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(messageDispatcher
  PUBLIC
  worldManager
  userManager
  networking
  PRIVATE
    ${Boost_LIBRARIES}
)

set_target_properties(messageDispatcher
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

install(TARGETS messageDispatcher
  ARCHIVE DESTINATION lib
)
