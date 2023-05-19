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


dependency("vorbis" "https://github.com/xiph/vorbis.git" "v1.3.4")
dependency("sfml" "https://github.com/SFML/SFML.git" "2.6.x")
dependency("catch2" "https://github.com/catchorg/Catch2.git" "v3.3.2")
