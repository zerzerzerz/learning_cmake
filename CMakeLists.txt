cmake_minimum_required(VERSION 3.10)
project(pybind11_example LANGUAGES CXX)

# check if use CXX compiler
if(CMAKE_CXX_COMPILER_LOADED)
    message(STATUS "CXX compiler loaded")
    message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
    message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
    # message compiler flag
    message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
else()
    message(FATAL_ERROR "CXX compiler not loaded")
endif()


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
    message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
    # show release flag
    message(STATUS "CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
endif()



# compile shared object with pybind11
add_subdirectory(pybind11)

# <variable_name> <help_string> <default_value>
option(subdir "Option of use add_subdirectory" ON)
message(STATUS "subdir: ${subdir}")
if(subdir STREQUAL ON)
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
    file(GLOB SRC_FILES src/*/*.cpp)
    message(STATUS "SRC_FILES: ${SRC_FILES}")
    pybind11_add_module(pybind11_example api/api.cpp ${SRC_FILES})
    target_include_directories(pybind11_example PRIVATE src/person src/my_math src/my_greet)
endif()
