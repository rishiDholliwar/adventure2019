add_library(world
        src/RoomController.cpp
        src/Room.cpp
        src/Door.cpp
        src/ExtendedDescription.cpp
        src/PigeonEXE.cpp)

add_executable(RoomControllerTest
        test/RoomControllerTest.cpp)

target_include_directories(world
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )


set_target_properties(world
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

target_link_libraries(world
        utility)

install(TARGETS world
  ARCHIVE DESTINATION lib
)

target_link_libraries(RoomControllerTest
        world)

