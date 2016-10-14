gcc memtest.c -fPIC -shared -o libmemtest.so # generate dynamic library
gcc main.c
export LD_PRELOAD="./libmemtest.so"
./a.out
