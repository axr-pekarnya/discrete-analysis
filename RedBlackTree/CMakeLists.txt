add_executable(RBTree main.cpp
    include/FileManager.hpp src/FileManager.cpp
    include/Formatter.hpp src/Formatter.cpp
    include/Item.hpp src/Item.cpp
    include/Node.hpp src/Node.cpp
    include/RedBlackTree.hpp src/RedBlackTree.cpp
)

target_include_directories(RBTree PRIVATE include)

