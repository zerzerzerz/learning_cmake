cmake_minimum_required(VERSION 3.10)
project(pybind11_example)

# compile shared object with pybind11
add_subdirectory(pybind11)

# <variable_name> <help_string> <default_value>
option(method "method" 0)
if(method STREQUAL 0)
    # method 0
    message(STATUS "method = subdirectory")
    pybind11_add_module(pybind11_example api/api.cpp)

    add_subdirectory(src/person)
    target_link_libraries(pybind11_example PRIVATE person)
    target_include_directories(pybind11_example PRIVATE src/person)

    add_subdirectory(src/my_math)
    target_link_libraries(pybind11_example PRIVATE my_math)
    target_include_directories(pybind11_example PRIVATE src/my_math)

    add_subdirectory(src/my_greet)
    target_link_libraries(pybind11_example PRIVATE my_greet)
    target_include_directories(pybind11_example PRIVATE src/my_greet)
    
else()
    message(STATUS "add all src files in src/*/*.cpp to pybind11_example")
    message(STATUS "SRC_FILES: ${SRC_FILES}")
    file(GLOB SRC_FILES src/*/*.cpp)
    pybind11_add_module(pybind11_example api/api.cpp ${SRC_FILES})
    target_include_directories(pybind11_example PRIVATE src/person src/my_math src/my_greet)
endif()
