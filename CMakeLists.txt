cmake_minimum_required(VERSION 3.0)
project(HW1_1)

set(CMAKE_CXX_CLANG_TIDY
        clang-tidy;
        -checks=${CMAKE_CURRENT_SOURCE_DIR}/cppfiles/;
        -header-filter=${CMAKE_CURRENT_SOURCE_DIR}/include/headers/;
        -warnings-as-errors=*;)

add_executable(
        build main.cpp
        Matrix.cpp
        VectorDouble.cpp
        )

add_executable(
        test
        Matrix.cpp
        VectorDouble.cpp
)

target_include_directories(build
        PRIVATE
        include/headers/)

target_include_directories(test
        PRIVATE
        include/headers/)
