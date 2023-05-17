add_executable(lab1 main.cpp
    src/RadixSort.cpp include/RadixSort.hpp
    include/Number.hpp
)

target_include_directories(lab1 PRIVATE include)

