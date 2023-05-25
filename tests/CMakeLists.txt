include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)



add_executable(RBTreeTest RBTreeTest.cpp
    include/GenerationUtils.hpp src/GenerationUtils.cpp
    ../RedBlackTree/include/FileManager.hpp ../RedBlackTree/src/FileManager.cpp
    ../RedBlackTree/include/Formatter.hpp ../RedBlackTree/src/Formatter.cpp
    ../RedBlackTree/include/Item.hpp ../RedBlackTree/src/Item.cpp
    ../RedBlackTree/include/Node.hpp ../RedBlackTree/src/Node.cpp
    ../RedBlackTree/include/RedBlackTree.hpp ../RedBlackTree/src/RedBlackTree.cpp

)

target_link_libraries(RBTreeTest PRIVATE GTest::GTest)
target_include_directories(RBTreeTest PRIVATE include)
target_include_directories(RBTreeTest PRIVATE ../RedBlackTree/include)

add_test(RBTreeTest RBTreeTest)

