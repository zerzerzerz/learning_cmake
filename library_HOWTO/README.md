# Program Library HOWTO
- [Program Library HOWTO](https://tldp.org/HOWTO/Program-Library-HOWTO/index.html)

## Static Libraries
- Static libraries are simply a collection of ordinary object files
  - 静态库是目标文件的打包集合
- Static libraries permit users to link to programs without having to recompile its code, saving recompilation time
  - 静态库可以直接被链接，不需要重新编译
- `ar rcs my_library.a file1.o file2.o`
  - 使用打包工具ar创建静态库
- In theory, code in static ELF libraries that is linked into an executable should run slightly faster (by 1-5%) than a shared library or a dynamically loaded library
  - 理论上静态库比动态库快一点点
```bash
gcc src/func.c -c -o lib/func.o
ar rcs lib/libfunc.a lib/func.o
gcc main.c -o main -Llib -lfunc
```

## Shared Libraries
- Shared libraries are libraries that are loaded by programs when they start.
- Soname
  - The soname is often used to provide version backwards-compatibility information. For instance, if versions 1.0 through 1.9 of the shared library "libx" provide identical interfaces, they would all have the same soname, e.g. "libx.so.1".
  - soname是so文件里面的一个字段，比如上面举了这样一个例子，不同小版本之间的lib有相同的interface，那么这些lib应该有相同的soname
  - The soname has the prefix `lib`, the `name of the library`, the phrase `.so`, followed by a `period` and a `version number` that is incremented whenever the interface changes
  - A fully-qualified soname includes as a `prefix` the `directory it's in`
- Real Name
  - the filename containing the actual library code
  - The real name adds to the soname a `period`, a `minor number`, `another period`, and the `release number`
- Linking Name
  - the name that the compiler uses when requesting a library, which is simply the soname without any version number
- Thus, `/usr/lib/libreadline.so.3` is a fully-qualified soname, which ldconfig would set to be a symbolic link to some realname like `/usr/lib/libreadline.so.3.0`. There should also be a linker name, `/usr/lib/libreadline.so` which could be a symbolic link referring to `/usr/lib/libreadline.so.3`.
- Starting up an ELF binary executable automatically causes the program loader to be loaded and run. On Linux systems, this loader is named `/lib/ld-linux.so.X` (where X is a version number). This loader, in turn, finds and loads all other shared libraries used by the program
- 当一个ELF可执行文件开始执行的时候，首先加载并运行loader `ld`，既是一个可执行文件，又是一个so动态链接库
- `/etc/ld.so.conf`默认会去这里寻找`.so`文件

## Environment Variables
- `LD_LIBRARY_PATH`，冒号分隔的目录集合，首先去这里搜索需要的lib

## soname的使用
```bash
gcc -shared -fPIC -o lib/libfunc.so.1.0 -Wl,-soname,libfunc.so.1 src/func.c

rm -f lib/libfunc.so.1
ln -s lib/libfunc.so.1.0 lib/libfunc.so.1

rm -f lib/libfunc.so
ln -s lib/libfunc.so.1 lib/libfunc.so

# 如果按照下面这么写，run的时候就不知道去哪找这个lib
# gcc main.c -L./lib -lfunc -o main.exe
# 加上-Wl,-rpath告诉程序运行的时候去这里找lib
# gcc main.c -L./lib -Wl,-rpath=$(realpath ./lib) -lfunc -o main.exe
gcc main.c -L./lib -Wl,-rpath=./lib -lfunc -o main.exe
```
- 编译动态库的时候，完整的版本号是1.0，我们存储这个文件的时候，文件名应当包含完整的版本号
- 同时编译的时候添加soname，比如我们想在1.X的全部版本中，对应的API不变，则soname里面应当写`*.so.1`
- 之后创建1.X版本的软链接，为`*.so.1`
- 之后创建这个库的软链接，指向某个大版本的软链接，这里是`*.so`
- 编译（链接）的时候，需要使用`-L`指定去哪里找lib，`-l`指定lib的名字，这样gcc会去对应目录下找`lib<lib_name>.so`的文件，这就要求名字中不能包含后面的版本号
- `-Wl,-rpath`指定一个链接器的参数，指定库所在的目录，是运行的时候去这里找 the run-time search path hard-coded in an executable file or library
- soname具体体现在调用`ldd`的过程，如下所示，注意到这里使用的lib是带着大版本的，
```bash
$ ldd main.exe 
    linux-vdso.so.1 (0x00007fff36a92000)
    libfunc.so.1 => /home/zhongruizhe/project/learning_cmake/library_HOWTO/lib/libfunc.so.1 (0x00007fbd0bc1e000)
    libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fbd0b82d000)
    /lib64/ld-linux-x86-64.so.2 (0x00007fbd0c022000)
```
- During compilation, the linker utilizes SONAME to identify the target library version from the library file. When using `gcc -l`, the linker searches for the `lib[NAME].so` link or file and retrieves its more precise SONAME

## 动态链接库搜索顺序
- `gcc`编译的时候指定的`-Wl,-rpath`
- 环境变量`LD_LIBRARY_PATH`指定的
- `/etc/ld.so.conf`这个配置文件指定的
- `/lib`
- `/usr/lib`