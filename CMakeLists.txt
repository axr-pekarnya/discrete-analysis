cmake_minimum_required(VERSION 3.20)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDART 17)

project(RED_BLACK_TREE)

enable_testing()

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()


add_subdirectory(tests)
add_subdirectory(RedBlackTree)
add_subdirectory(Apostolico-Giancarlo)

