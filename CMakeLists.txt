cmake_minimum_required(VERSION 3.20)
set(project_name EntityManager)
set(project_version 1.0.0)
project(
    ${project_name}
    LANGUAGES CXX
    VERSION ${project_version}
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_TEST OFF CACHE BOOL "When ON allows for building a target test")

set(BUILD_SHARED_LIBS OFF)
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_DOC OFF)
set(SFML_BUILD_NETWORK OFF)
set(SFML_BUILD_AUDIO OFF)
set(SFML_BUILD_GRAPHICS ON)
set(SFML_BUILD_WINDOW ON)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/dependencies.cmake)

find_package(SFML REQUIRED COMPONENTS system window graphics REQUIRED)

add_executable(${project_name} "src/main.cpp")

set(entity_manager_lib EntityManagerLib)
set(entity_manager_source
    "src/entity.cpp"
    "src/vec2.cpp"
    "src/entity_manager.cpp"
    "src/game.cpp"
    "src/window.cpp"
)
add_library(${entity_manager_lib} 
        STATIC ${entity_manager_source})
target_include_directories(${entity_manager_lib}
    PUBLIC "include/entity"
        "include/components"
        "include/geometry")
target_link_libraries(${entity_manager_lib}
    PUBLIC sfml-system sfml-window sfml-graphics)

target_link_libraries(${project_name} PUBLIC ${entity_manager_lib})

if(BUILD_TEST)
    message(STATUS "Including ${CMAKE_CURRENT_LIST_DIR}/cmake/tests.cmake")
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/tests.cmake)
    target_compile_definitions(${entity_manager_lib}
        PUBLIC
            BUILD_TEST)
endif()

