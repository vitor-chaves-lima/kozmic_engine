add_executable(sandbox
        src/win32_window.cc
        src/win32_utils.cc
        src/main.cc
)

target_include_directories(sandbox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
configure_target(sandbox)
