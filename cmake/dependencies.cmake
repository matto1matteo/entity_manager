
function(dependency dependency_name repository tag)
    include(FetchContent)
    message(STATUS "Fetching: ${repository} @ ${tag}")

    if(tag STREQUAL "")
        message(FATAL_ERROR "Invalid tag for ${repository}")
    endif()
    
    FetchContent_Declare(
        ${dependency_name}
        GIT_REPOSITORY "${repository}"
        GIT_TAG "${tag}"
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        OVERRIDE_FIND_PACKAGE
    )
endfunction()

