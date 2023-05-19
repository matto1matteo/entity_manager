find_package(Catch2)


set(tests_path "${CMAKE_CURRENT_SOURCE_DIR}/tests/")
add_executable(tests
    ${tests_path}/geometry/vec2.cpp)
target_link_libraries(tests
    PUBLIC
        ${entity_manager_lib}
        Catch2::Catch2WithMain)
