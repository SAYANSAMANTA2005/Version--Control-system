@echo off

echo Compiling the code...

g++ Text.cpp -static -o Text.exe

echo Compilation finished. Executable created: Text.exe

echo Running the executable...
.\Text.exe
pause
