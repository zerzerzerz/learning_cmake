cmake_minimum_required(VERSION 3.10)
project(test_subdir LANGUAGES CXX VERSION 1.0.0)

add_subdirectory(subdir1)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} sub::lib1)
