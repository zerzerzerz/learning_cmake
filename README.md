# README
## Run
```bash
mkdir build && cd build
cmake ..
make -j
python ../test.py
```

## Hard Link and Symbol Link
### 文件的创建过程
- data写入硬盘
- 创建一个reference，叫做inode，指向data的起始地址
- filename被创建，指向inode
### 创建hard link
- 创建一个新的filename也指向这个inode
- 因此修改其中一个，会导致另一个的修改
- 删掉源文件，新的那个还在
- 只能指向文件
### 创建symbol link
- 可以指向文件或文件夹
- 指向文件
  - 两者同步
  - 删除symbol link，源文件还在
  - 删除源文件，symbol link还在但是失效
- 指向文件夹
  - 想要删除symbol link，需要`rm dir`
  - 想要删除symbol link里面的内容，需要`rm dir/`


## CMake基础知识
### 缓存变量cache variable
- `set(<variable> <value> CACHE <type> <docstring> [FORCE])`，其中FORCE，当定义一个cache的时候，加不加都行，但修改的时候，则必须添加FORCE，否则就会修改失败
- 缓存变量有着global scope，而普通变量只在当前CMakeLists.txt里面生效
- 用于user-defined configuration的时候，cache variable可能是个更好的选择

### target_include_directories
- 预处理阶段，每个target在搜索头文件的时候，维护两个变量`INCLUDE_DIRECTORIES`和`INTERFACE_INCLUDE_DIRECTORIES`。前者只用于当前target去找头文件，而后者将加到其他依赖于当前target的目标文件的`INCLUDE_DIRECTORIES`
- 因此，对于`PUBLIC`，目录加到二者当中
- 对于`INTERFACE`，目录只加到`INTERFACE_INCLUDE_DIRECTORIES`，也就是自己不用，给其他依赖于自己的target用
- `PRIVATE`，只有当前target用，不给其他target用
- 什么叫做target之间的依赖？比如当前target编译成一个lib，被其他target链接了


### target_link_libraries
- `PUBLIC`, linking to the current target and providing the interface to the other targets that have dependencies on the current target
- `PRIVATE`, only be used for linking to the current target
- `INTERFACE`, only be used for providing the interface to the other targets that have dependencies on the current target