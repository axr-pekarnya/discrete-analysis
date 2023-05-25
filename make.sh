#!/bin/bash

exe_file="main"
main_dir="/home/axr/prog/discrete-analysis"
tmp_dir="${main_dir}/.build"

mkdir ${tmp_dir}
cd ${tmp_dir}

cmake ${main_dir}
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ${main_dir}
cmake --build . --target RBTreeTest
cmake --build . --target AGTest
ctest -V

mv compile_commands.json ${main_dir}

