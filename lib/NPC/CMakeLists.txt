add_library(NPC src/NPC.cpp)
find_package(Boost 1.66 COMPONENTS system REQUIRED)

target_include_directories(NPC
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${Boost_INCLUDE_DIR}
        )

target_link_libraries(NPC
		utility
                uniqueID
        )

install(TARGETS NPC
        ARCHIVE DESTINATION lib
        )
