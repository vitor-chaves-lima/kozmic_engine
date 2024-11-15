get_directory_sources("${CMAKE_SOURCE_DIR}/lib/src/platform/${KOZMIC_PLATFORM}" PLATFORM_SOURCES)
get_directory_sources("${CMAKE_SOURCE_DIR}/lib/src/core" CORE_SOURCES)

check_graphics_libraries_available(AVAILABLE_GRAPHICS_LIBRARIES)
message(STATUS "Available graphics libraries: ${AVAILABLE_GRAPHICS_LIBRARIES}")

set(KOZMIC_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/include)

add_library(kozmic
        ${PLATFORM_SOURCES}
        ${CORE_SOURCES}
)

target_include_directories(kozmic PUBLIC ${KOZMIC_INCLUDE_DIR})
set_target_properties(kozmic PROPERTIES LINKER_LANGUAGE CXX)

configure_target(kozmic)
