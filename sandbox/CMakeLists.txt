add_executable(sandbox
        src/main.cc
)

target_include_directories(sandbox PUBLIC ${KOZMIC_INCLUDE_DIR})
target_link_libraries(sandbox PUBLIC kozmic)
configure_target(sandbox)
