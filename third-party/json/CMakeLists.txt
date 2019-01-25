add_library(json
			json.hpp)

set_target_properties(json
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

install(TARGETS json
  ARCHIVE DESTINATION lib
)
