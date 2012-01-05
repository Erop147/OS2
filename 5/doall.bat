gcc -c main.c -o main.o
nasm -f win32 mult.asm -o mult.o
gcc main.o mult.o -o main.exe