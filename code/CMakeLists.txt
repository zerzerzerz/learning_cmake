# ./code/CmakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(square VERSION 1.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(USE_EXTRA_LIB "weather to use my extra lib" ON)
if(${USE_EXTRA_LIB})
    add_subdirectory(my_extra_lib)
    list(APPEND my_extra_libs my_extra_lib)
    list(APPEND my_extra_includes ${PROJECT_SOURCE_DIR}/my_extra_lib)
endif()

add_subdirectory(my_func)

configure_file(config.h.in config.h)
set(src_files square.cpp)
add_executable(${PROJECT_NAME} ${src_files})

target_link_libraries(${PROJECT_NAME} PUBLIC my_func ${my_extra_libs})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/my_func ${my_extra_includes})

