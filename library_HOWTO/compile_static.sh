gcc src/func.c -c -o lib/func.o
ar rcs lib/libfunc.a lib/func.o
gcc main.c -o main_static.exe -Llib -lfunc
