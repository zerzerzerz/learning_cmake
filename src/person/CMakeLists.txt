add_library(person SHARED person.cpp)
target_link_libraries(person PRIVATE my_greet)
target_include_directories(person PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../my_greet)