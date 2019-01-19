add_library(world
            src/Area.cpp
            src/Room.cpp
            src/World.cpp
            src/Door.cpp test/WorldTest.cpp)

add_executable(test
            test/WorldTest.cpp)

target_include_directories(world
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )