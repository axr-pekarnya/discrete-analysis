cmake_minimum_required(VERSION 3.20)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDART 17)

project(BOYER_MOORE)

enable_testing()

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(main main.cpp
    src/ZFunction.cpp include/ZFunction.hpp
    src/NFunction.cpp include/NFunction.hpp
    src/LFunction.cpp include/LFunction.hpp
    src/LsFunction.cpp include/LsFunction.hpp
    src/GoodSuffix.cpp include/GoodSuffix.hpp
    src/SymbolTable.cpp include/SymbolTable.hpp
    src/SuccesfullShift.cpp include/SuccesfullShift.hpp
    src/ParsingUtils.cpp include/ParsingUtils.hpp
    src/AGSearch.cpp include/AGSearch.hpp
)

target_include_directories(main PRIVATE include)

