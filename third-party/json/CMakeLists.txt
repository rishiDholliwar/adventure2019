add_library(json
			json.hpp)

target_include_directories(json
  PUBLIC
    $<INSTALL_INTERFACE:.>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

set_target_properties(json
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

install(TARGETS json
  ARCHIVE DESTINATION lib
)
