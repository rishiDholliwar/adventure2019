
add_library(userManager
  src/User.cpp
  src/UserManager.cpp)

find_package(Boost 1.66 COMPONENTS system REQUIRED)

target_include_directories(userManager
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(userManager
  PRIVATE
    ${Boost_LIBRARIES}
)

set_target_properties(userManager
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

install(TARGETS userManager
  ARCHIVE DESTINATION lib
)
