gcc -shared -fPIC -o lib/libfunc.so.1.0 -Wl,-soname,libfunc.so.1 src/func.c

cd lib
rm -f libfunc.so.1
ln -s libfunc.so.1.0 libfunc.so.1

rm -f libfunc.so
ln -s libfunc.so.1 libfunc.so

cd ..
# gcc main.c -L./lib -lfunc -o main.exe
# gcc main.c -L./lib -Wl,-rpath=$(realpath ./lib) -lfunc -o main.exe
gcc main.c -L./lib -Wl,-rpath=./lib -lfunc -o main_dynamic.exe

