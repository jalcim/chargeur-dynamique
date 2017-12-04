gcc -fPIC -c -Wall -I. test.c
gcc -shared -Wl,-soname,libtest.so.1 -Wall test.o -o libtest.so.1.0
cp ./libtest.so.1.0 ./libtest.so
sudo cp libtest.so /usr/lib
sudo cp libtest.so.1.0 /usr/lib
cp test.h /tmp/fstest/include
