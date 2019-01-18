
add_library(networking
  src/Server.cpp
  src/Client.cpp
        ../MessageDispatcher/src/MessageDispatcher.cpp ../MessageDispatcher/include/MessageDispatcher.h ../WorldManager/src/WorldManager.cpp ../WorldManager/include/WorldManager.h ../User/src/User.cpp ../User/include/User.h ../User/src/UserManager.cpp ../User/include/UserManager.h ../Ultility/Ultility.cpp ../Ultility/Ultility.h)

find_package(Boost 1.66 COMPONENTS system REQUIRED)

target_include_directories(networking
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(networking
  PRIVATE
    ${Boost_LIBRARIES}
)

set_target_properties(networking
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

install(TARGETS networking
  ARCHIVE DESTINATION lib
)

