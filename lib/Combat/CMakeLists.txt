add_library(combat
        src/Combat.cpp
        src/CombatController.cpp
        include/Combat.h
        include/CombatController.h
        )

target_include_directories(combat
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        )

target_link_libraries(combat
        PUBLIC
        utility
        Character
        PRIVATE
        ${Boost_LIBRARIES}
        )