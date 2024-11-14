get_platform_sources(${KOZMIC_PLATFORM} PLATFORM_SOURCES)
message(STATUS "Platform sources: ${PLATFORM_SOURCES}")

set(KOZMIC_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/include)

add_library(kozmic
        ${PLATFORM_SOURCES}
)

target_include_directories(kozmic PUBLIC ${KOZMIC_INCLUDE_DIR})
set_target_properties(kozmic PROPERTIES LINKER_LANGUAGE CXX)

configure_target(kozmic)
