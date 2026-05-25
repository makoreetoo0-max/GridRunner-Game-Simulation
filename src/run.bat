@echo off

g++ -std=c++23 -fmodules-ts -c libGame.cpp

g++ -std=c++23 -fmodules-ts -c main.cpp

g++ -std=c++23 -fmodules-ts libGame.o main.o -o main.exe

main.exe 10 10 5 5 5

pause