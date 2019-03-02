add_executable(test_character
        src/test_character.cpp src/Character.cpp include/Character.h)

add_library(Character src/Character.cpp)
find_package(Boost 1.66 COMPONENTS system REQUIRED)

target_include_directories(Character
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${Boost_INCLUDE_DIR}
        )

set_target_properties(test_character
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 17
        PREFIX ""
        )

target_link_libraries(Character
        PUBLIC
                Inventory
		utility
                uniqueID
        )

target_link_libraries(test_character
        Character
        Object
        Inventory
        utility
        uniqueID
        )

install(TARGETS Character
        ARCHIVE DESTINATION lib
        )

install(TARGETS test_character
        RUNTIME DESTINATION lib
        )