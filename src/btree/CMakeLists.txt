cmake_minimum_required(VERSION 3.23)
project(pro_alg_3_btree)

set(CMAKE_CXX_STANDARD 14)

add_executable(pro_alg_3_btree main.cpp b_tree.cpp b_tree.h b_tree_node.cpp b_tree_node.h unit_testing.cpp unit_testing.h my_unit_test.cpp my_unit_test.h)
