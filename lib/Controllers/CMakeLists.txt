add_library(controllers
        src/CharacterController.cpp src/ObjectController.cpp src/ResetController.cpp)

find_package(Boost 1.66 COMPONENTS system REQUIRED)

target_include_directories(controllers
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${Boost_INCLUDE_DIR}
        )

target_link_libraries(controllers
PRIVATE
        world
        Character
        Object
        Inventory
        utility
        Reset
        ${Boost_LIBRARIES}
        )

set_target_properties(controllers
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 17
        )

install(TARGETS controllers
        ARCHIVE DESTINATION lib
        )
