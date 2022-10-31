# Notes for cmake
## 教程链接
- [CMake tutorials](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
- 文件夹目录结构
```
build/
code/
    main.cpp
    CMakeLists.txt
```
### 编写`CMakeLists.txt`
```cmake
# ./build/CmakeLists.txt
# 指定cmake的最低版本号，注意VERSION需要大写
cmake_minimum_required(VERSION 3.10)
# 指定项目的名称
project(square)
# 第一个参数是生成的文件的名字，第二个是参与编译的源文件
add_executable(square square.cpp)
```
### 运行
  - 首先cd到build文件夹下，执行`cmake ../code`，`../code`表示`CmakeLists.txt`文件所在的目录
  - 刚刚执行的一步叫做**构建**，生成一堆cmakefiles，但是没有可执行文件生成
  - 之后就能看到在build文件夹下，生成了一堆cmakefiles
  - 最后在这堆cmakefiles所在的目录（这里是build目录），执行`cmake --build .`，就会在那一堆cmakefiles所在的目录，生成对应的可执行文件
  - 这一步称为**编译**
### 设置变量
  - 在cmake文件中，也可以设置变量名，基本的语法是`set(var_name var_value)`
  - 引用变量的时候，用`${var_name}`即可
```cmake
# ./build/CmakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(square_variable)
# 将src_files设置为square.cpp
set(src_files square.cpp)
# PROJECT_NAME这个变量本身cmake就有，用来指示项目名称
add_executable(${PROJECT_NAME} ${src_files})
```
### 指定项目的版本号
  - 可以在CmakeLists.txt中指定项目的版本号，并且传递给C++文件
```cmake
# ./code/CmakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(square VERSION 1.0)
configure_file(config.h.in config.h)
set(src_files square.cpp)
add_executable(${PROJECT_NAME} ${src_files})
# 这句话要加在add_executable后面，不然${PROJECT_NAME}这个目录就会没有build
# ${PROJECT_BINARY_DIR}表示当前工程二进制目录，编译产物都放在这里
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})
```
```cpp
// 这个文件和*.cpp放在一个目录下面
// -- ./code/config.h.in

// 运行cmake ../code之后，就能在build/config.h找到这个文件，发现version已经被替换了

// 必须这么命名
// @${PROJECT_NAME}_VERSION_MAJOR@
// @${PROJECT_NAME}_VERSION_MINOR@
#define VERSION_MAJOR @square_VERSION_MAJOR@
#define VERSION_MINOR @square_VERSION_MINOR@
```
### 指定C++标准
```cmake
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
```

### 添加库
- 这里的库指的是自己编写的库
- 此时文件结构如下
```
build/
code/
    my_func/
        my_func.cpp
        my_func.h
        CMakeLists.txt
    CMakeLists.txt
    config.h.in
    square.cpp
```
- 库文件较为简单，分为`.h`声明文件和`.cpp`定义（实现）文件
```cpp
// ./code/my_func/my_func.h
#ifndef __MY_FUNC_H__
#define __MY_FUNC_H__
int my_sum(const int&a, const int&b);
#endif
```
```cpp
// ./code/my_func/my_func.cpp
#include "my_func.h"
int my_sum(const int&a, const int&b){
    return a+b;
}
```
- 在`./code`下面也需要创建一个CMakeLists.txt如下，表示添加一个库文件
```cmake
# ./code/my_func/CMakeLists.txt
add_library(my_func my_func.cpp)
```
- 同时修改顶层目录下面的CMakeLists.txt
```cmake
# ./code/CmakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(square VERSION 1.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 指定库所在的子目录，该子目录需要包含实现文件以及CMakeLists.txt
add_subdirectory(my_func)

configure_file(config.h.in config.h)
set(src_files square.cpp)
add_executable(${PROJECT_NAME} ${src_files})

# 让target文件可以使用这个库
target_link_libraries(${PROJECT_NAME} PUBLIC my_func)

# 增加搜索目录，让my_func.h可以被搜索到
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/my_func)
```

## 将一个库设为可选
- 可以让用户自己指定一个库是否可选
- 在`./code`目录中新建一个库，叫做`my_extra_lib`
- 修改顶层`CMakeLists.txt`
```cmake
# ./code/CmakeLists.txt
# option(<variable_name> "description" [default_value])
option(USE_EXTRA_LIB "weather to use my extra lib" ON)
if(${USE_EXTRA_LIB})
    add_subdirectory(my_extra_lib)
    # 创建一个叫做my_extra_libs的list，然后将my_extra_lib把它append进去
    list(APPEND my_extra_libs my_extra_lib)
    list(APPEND my_extra_includes ${PROJECT_SOURCE_DIR}/my_extra_lib)
endif()
# 这里需要cmakedefine来决定是否生成新的宏
configure_file(config.h.in config.h)
# 把需要link的库以及需要target搜索的目录加进去
target_link_libraries(${PROJECT_NAME} PUBLIC my_func ${my_extra_libs})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/my_func ${my_extra_includes})
```
- 还需要修改这个配置文件
```cpp
// -- ./code/config.h.in
#define VERSION_MAJOR @square_VERSION_MAJOR@
#define VERSION_MINOR @square_VERSION_MINOR@
// 会根据CMakeLists里面是否为ON来确定是否有这个宏
#cmakedefine USE_EXTRA_LIB
```
- 主文件里面也要根据可选库做出相应的修改
```cpp
// ./code/square.cpp
#ifdef USE_EXTRA_LIB
#include "my_extra_lib.h"
#endif
using namespace std;
int main(){
    #ifdef USE_EXTRA_LIB
        extra_func();
    #else
        cout << "No extra lib" << endl;
    #endif
    return 0;
}
```
- 在命令行中修改选项
```bash
# 一个连字符
# 前面加D（不知道为什么）
# ON和OFF记得大写~
cmake ../code -DUSE_EXTRA_LIB=OFF
```

## 现代化管理可用库
- 现在介绍一种新的方法管理库，让使用者决定是否使用，这里新建的库为`code/my_math`
- 首先来看`code/my_math`下面的cmakelists
```cmake
# code/my_math/CMakeLists.txt
# 库的名字 库的源文件
add_library(my_math my_math.cpp)
# Remember INTERFACE means things that consumers require but the producer doesn't.
# ${CMAKE_CURRENT_SOURCE_DIR}指的是当前cmakelists所在目录
target_include_directories(my_math INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
```
- 之后修改`code/CMakeLists.txt`
```cmake
if(${USE_MY_MATH})
    # 删掉关于lib所在路径的语句，只需要将这个使用的lib加上即可
    add_subdirectory(my_math)
    list(APPEND my_extra_libs my_math)
endif()
# 这里一样，删掉库的路径导入，不是完全删掉，是删掉库路径的include
target_link_libraries(${PROJECT_NAME} PUBLIC my_func ${my_extra_libs})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/my_func)
```
- 此时完整的`code/CMakeLists.txt`如下
```cmake
# ./code/CmakeLists.txt

# set cmake minimum version
cmake_minimum_required(VERSION 3.10)
project(square VERSION 1.5)


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
set(src_files square.cpp)
add_executable(${PROJECT_NAME} ${src_files})


# link libs to executable target
target_link_libraries(${PROJECT_NAME} PUBLIC my_func ${my_extra_libs})


# speficy the header location
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/my_func)
```