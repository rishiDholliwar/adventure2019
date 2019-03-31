add_library(ttt
        src/Board.cpp  src/TicTacToe.cpp include/Cell.h src/Cell.cpp include/AI.h src/AI.cpp
        include/Constants.h)

target_include_directories(ttt
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        src
        )

target_link_libraries(ttt
        PUBLIC
        utility
        )
