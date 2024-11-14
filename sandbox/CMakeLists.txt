add_executable(sandbox src/main.cc
        src/win32_window.cc
        src/main.cc
        src/win32_utils.cc
)

target_include_directories(sandbox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)