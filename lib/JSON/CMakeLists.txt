add_library(jsonThingy
        JSONThingy.cpp)

find_package(Boost 1.66 COMPONENTS filesystem system REQUIRED)

target_include_directories(jsonThingy
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        ${Boost_INCLUDE_DIR}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )


target_link_libraries(jsonThingy
        PUBLIC
        commandHandler
        Character
        Object
        Inventory
        controllers
        json
        controllers
        world
        Reset
        ${Boost_LIBRARIES}
        PRIVATE
        utility
        uniqueID
        stringModifier
        )


set_target_properties(jsonThingy
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 17
        )
install(TARGETS jsonThingy
        ARCHIVE DESTINATION lib
        )


add_executable(jsonThingyTest
       main.cpp)

set_target_properties(jsonThingyTest
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 17
        PREFIX "")


target_link_libraries(jsonThingyTest
        jsonThingy
        utility
        uniqueID
        stringModifier
        ${Boost_LIBRARIES})


install(TARGETS jsonThingyTest
        RUNTIME DESTINATION bin)
