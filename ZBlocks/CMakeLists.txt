cmake_minimum_required(VERSION 3.20)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDART 17)

project(ZBlocks)

enable_testing()

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(ZBlocks main.cpp
    include/ZFunction.hpp src/ZFunction.cpp
)

target_include_directories(ZBlocks PRIVATE include)

