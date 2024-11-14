set(KOZMIC_TRUE 1)
set(KOZMIC_FALSE 0)

function(configure_target target)
    if (TARGET ${target})
        if (KOZMIC_UNICODE_SUPPORT)
            target_compile_definitions(${target} PRIVATE KOZMIC_UNICODE_SUPPORT=KOZMIC_TRUE)
            target_compile_definitions(${target} PRIVATE UNICODE _UNICODE)
        else ()
            target_compile_definitions(${target} PRIVATE KOZMIC_UNICODE_SUPPORT=KOZMIC_FALSE)
        endif (KOZMIC_UNICODE_SUPPORT)
    else ()
        message(FATAL_ERROR "Target '${my_target}' doesn't exists.")
    endif ()
endfunction()