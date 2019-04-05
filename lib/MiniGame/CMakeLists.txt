add_library(miniGame
        src/MiniGameController.cpp)



target_include_directories(miniGame
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        src
        )


target_link_libraries(miniGame
       PUBLIC
       ttt
       utility
        )

add_subdirectory(Games/TicTacToe)



