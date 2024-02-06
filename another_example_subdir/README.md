# README
- 一个更好的例子来展示如何编译lib
- 参考[https://github.com/ttroy50/cmake-examples/tree/master/02-sub-projects/A-basic](https://github.com/ttroy50/cmake-examples/tree/master/02-sub-projects/A-basic)

## lib的文件结构
```txt
subdir1/
├── CMakeLists.txt
├── include
│   └── subdir1
│       └── lib1.h
└── src
    └── lib1.cpp

3 directories, 3 files
```
- 其中的cmake这么写
```cmake
project(sublib1)
add_library(${PROJECT_NAME} src/lib1.cpp)
add_library(sub::lib1 ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC include)
```
- alias那个地方的作用是，当其他target link这个lib的时候，会自动把这个lib的`INTERFACE_INCLUDE_DIRECTORIES`给加到当前target
- target在link lib的时候，要注意使用alias lib


## main的配置
- top level的cmake就这么写
```cmake
cmake_minimum_required(VERSION 3.10)
project(test_subdir LANGUAGES CXX VERSION 1.0.0)

add_subdirectory(subdir1)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} sub::lib1)
```
- 观察到在main的cmake里面我们不再需要`target_include_directories`，我们可以直接`#include "subdir1/lib1.h"`就很方便

## 配置Intelligence
- 创建`.vscode/settings.json`并写入以下内容
```json
{
    "C_Cpp.default.configurationProvider": "ms-vscode.cmake-tools"
}
```
- 这样在使用vscode build之后，就能正确进行跳转之类的操作了