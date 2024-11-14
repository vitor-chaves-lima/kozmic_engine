add_executable(sandbox
        src/win32_window.cc
        src/win32_utils.cc
        src/main.cc
)

if (KOZMIC_UNICODE_SUPPORT)
    target_compile_definitions(sandbox PRIVATE UNICODE _UNICODE)
endif (KOZMIC_UNICODE_SUPPORT)

target_include_directories(sandbox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)