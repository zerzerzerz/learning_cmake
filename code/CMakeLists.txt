# ./code/CmakeLists.txt

# set cmake minimum version
cmake_minimum_required(VERSION 3.10)
project(main VERSION 1.5)


# set variable names, which src files
set(src_files main.cpp)


# set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# set optional libs
option(USE_EXTRA_LIB "weather to use my extra lib" ON)
if(${USE_EXTRA_LIB})
    add_subdirectory(my_extra_lib)
    list(APPEND my_extra_libs my_extra_lib)
endif()


# set optional libs
option(USE_MY_MATH "Wheater to use my math lib" ON)
if(${USE_MY_MATH})
    add_subdirectory(my_math)
    list(APPEND my_extra_libs my_math)
endif()

# set a lib which must be used
add_subdirectory(my_func)


# set configure file
configure_file(config.h.in config.h)


# set variable and exe filename and src files
add_executable(${PROJECT_NAME} ${src_files})


# link libs to executable target
target_link_libraries(${PROJECT_NAME} PUBLIC my_func ${my_extra_libs})


# speficy the header location
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/my_func)