gcc -shared -fPIC -o lib/libfunc.so.1.0 -Wl,-soname,libfunc.so.1 src/func.c

cd lib
ln -sf libfunc.so.1.0 libfunc.so.1
ln -sf libfunc.so.1 libfunc.so
cd ..

# gcc main.c -L./lib -lfunc -o main.exe
# gcc main.c -L./lib -Wl,-rpath=$(realpath ./lib) -lfunc -o main.exe
gcc main.c -Llib -Wl,-rpath=./lib -lfunc -o main_dynamic.exe

