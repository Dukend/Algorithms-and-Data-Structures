cmake_minimum_required(VERSION 3.5)
project(solution)
add_executable(solution main.cpp TData.cpp TAvl.cpp TAvlFinal.cpp)
set_target_properties(solution PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
