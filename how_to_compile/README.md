# README
## 编译过程
- 预编译
- 编译
- 汇编
- 链接
  - 静态链接，将汇编生成的目标文件`.o`以及引用的库一起打包生成可执行文件，命名规范为`lib[library_name].a`，需要使用打包工具`ar`
  - 动态链接，不需要其他工具，使用编译器即可，命名规范为`lib[library_name].so`


## 生成目标文件
```bash
g++ test.cpp -c -o test.o
g++ main.cpp -c -o main.o
```

## 编译生成静态库
- 实际上将文件进行打包(a = archive)
```bash
ar crsv libtest.a test.o
```

## 静态链接
```bash
g++ main.o libtest.a
```

## 编译生成动态链接库
```bash
g++ test.cpp -fPIC -shared -Wl,-soname,libtest.so -o libtest.so
```
- `PIC` = Position Indepent Code
- `-Wl,-soname,libtest.so`指定别名

## 动态链接
```bash
g++ main.o libtest.so
g++ main.o -L. -ltest
```
- 链接的时候需要使用lib的realpath而不是soname
- 如果使用第二种形式进行链接，`-l<library_name>`指定需要链接的库，`-L.`指定需要去哪个目录进行连接，比如这里选的是当前目录。需要注意的是这种方式库的名字必须是`lib<XXX>.so, lib<XXX>.a`这样的，像`libtest.so.0.1`这种带着版本号的就不行

## 编译
- 编译静态库，使用`ar`将`.o`文件进行合并
- 编译动态库，使用`ld`链接器，执行相似段合并、地址偏移量计算，发生了有效的链接


## 链接
- Linux里面的ELF文件（Executable and Linkable Format），包含可重定向文件、可执行文件、共享目标文件
- 可重定向文件，包含了数据和代码，可以用来链接成可执行文件或者共享目标文件，常见的有目标文件`.o`以及静态库`.a`
- 通常情况下，每个参与编译的文件都会生成一个目标文件`.o`，这些目标文件彼此之间是互相独立的，虽然某个目标文件A可能引用了某个外部函数，但是在这个阶段仅仅是一个未定义的外部符号而已，并不知道他的实际实现在哪里
- 还需要链接器`ld`将这些独立的目标文件`.o`组装起来，这个过程就是链接，连接过程会对目标文件进行相似段合并，然后为每个段以及符号分配空间地址、进行符号解析、重定向
- 动态库链接静态库，静态库中的`.o`文件会被链接器`ld`依次遍历，把动态库需要的部分加入到相似段合并的过程中。实际上，这个过程发生在编译动态库并链接静态库中，静态库参与动态库的生成
- 静态库链接静态库，这条命令会被cmake忽略，因为编译一个静态库不会发生链接过程，只需要使用`g++ XXX.cpp -c`和`ar`命令，不涉及到链接器`ld`，也就不会检查符号依赖之类的东西
- 静态库链接动态库，可以，但是用的时候不仅需要链接这个静态库本身，还需要链接包含了它所引用的符号的库