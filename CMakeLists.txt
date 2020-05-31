cmake_minimum_required(VERSION 3.16)
set(This hash_tree_lib)

project(${This})

set(CMAKE_CXX_STANDARD 17)

set(Sources
    hash_tree.hpp
)

add_library(${This} STATIC ${Sources})
set_target_properties(${This} PROPERTIES LINKER_LANGUAGE CXX)

#######################################
# Test
enable_testing()
add_subdirectory(test)
