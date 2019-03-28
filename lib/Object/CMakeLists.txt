add_executable(test_object
                src/test_object.cpp )

add_library(Object 
                src/Object.cpp 
                src/Extra.cpp)
add_library(Inventory src/Inventory.cpp)
find_package(Boost 1.66 COMPONENTS system REQUIRED)

target_include_directories(Object
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${Boost_INCLUDE_DIR}
        )

target_include_directories(Inventory
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${Boost_INCLUDE_DIR}
        )

set_target_properties(test_object
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 17
        PREFIX ""
        )

target_link_libraries(test_object
        Object
        )

target_link_libraries(Object
        utility
        uniqueID
        )

target_link_libraries(Inventory
        PUBLIC
                Object
                jsonObjects
        )

install(TARGETS Object
        ARCHIVE DESTINATION lib
        )

install(TARGETS Inventory
        ARCHIVE DESTINATION lib
        )

install(TARGETS test_object
        RUNTIME DESTINATION lib
        )
