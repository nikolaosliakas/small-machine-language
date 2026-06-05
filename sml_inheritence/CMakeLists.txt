cmake_minimum_required(VERSION 4.0)
project(small_machine_language)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(lib)
add_executable(small_machine_language
        main.cpp
        )
target_link_libraries(small_machine_language PRIVATE SMLlib)


