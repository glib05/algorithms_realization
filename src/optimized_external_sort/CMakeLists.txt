cmake_minimum_required(VERSION 3.23)
project(pro_alg_1_merge)

set(CMAKE_CXX_STANDARD 14)

add_executable(pro_alg_1_merge main.cpp external_sort.cpp external_sort.h merge_sort.cpp merge_sort.h internal_sort.cpp internal_sort.h file_functions.cpp file_functions.h my_unit_test.cpp my_unit_test.h unit_testing_sorting.cpp unit_testing_sorting.h)
