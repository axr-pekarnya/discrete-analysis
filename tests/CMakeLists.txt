include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)



file(GLOB_RECURSE RBTreeIncludes ../RedBlackTree/include/*.hpp)
file(GLOB_RECURSE RBTreeSources ../RedBlackTree/src/*.cpp)

add_executable(RBTreeTest RBTreeTest.cpp
    include/GenerationUtils.hpp src/GenerationUtils.cpp
    ${RBTreeIncludes} ${RBTreeSources}    
)

target_link_libraries(RBTreeTest PRIVATE GTest::GTest)
target_include_directories(RBTreeTest PRIVATE include)
target_include_directories(RBTreeTest PRIVATE ../RedBlackTree/include)

add_test(RBTreeTest RBTreeTest)



file(GLOB_RECURSE AGIncludes ../Apostolico-Giancarlo/include/*.hpp)
file(GLOB_RECURSE AGSources ../Apostolico-Giancarlo/src/*.cpp)

add_executable(AGTest AGTest.cpp
    include/GenerationUtils.hpp src/GenerationUtils.cpp
    ${AGIncludes} ${AGSources} 
)

target_link_libraries(AGTest PRIVATE GTest::GTest)
target_include_directories(AGTest PRIVATE include)
target_include_directories(AGTest PRIVATE ../Apostolico-Giancarlo/include)

add_test(AGTest AGTest)

