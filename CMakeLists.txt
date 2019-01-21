cmake_minimum_required(VERSION 3.12)
project(AlterSpace)

set(PACKAGE_NAME AlterSpace)
set(PACKAGE_VERSION 0.1)
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
# Sorry Nick, we don't actually want the bug reports
set(PACKAGE_BUGREPORT "wsumner@sfu.ca")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fno-rtti")
set(CMAKE_CXX_FLAGS_DEBUG 
    "-O0 -g -fsanitize=address,undefined -fno-omit-frame-pointer"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

# And the project header and library paths
link_directories(${LIBRARY_OUTPUT_PATH})
set(CMAKE_TEMP_LIBRARY_PATH "${PROJECT_BINARY_DIR}/lib")

set(NETWORKING_LIB_DIRECTORY "web-socket-networking/lib")
IF(NOT EXISTS NETWORKING_LIB_DIRECTORY)
	EXECUTE_PROCESS(COMMAND git submodule update --init)
ENDIF()

add_subdirectory(lib)
add_subdirectory(tools)
add_subdirectory(web-socket-networking/lib)
