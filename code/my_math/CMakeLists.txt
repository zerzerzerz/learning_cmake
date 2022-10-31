# code/my_math/CMakeLists.txt
add_library(my_math my_math.cpp)
target_include_directories(my_math INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})