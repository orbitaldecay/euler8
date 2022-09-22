gcc -m64 -O2 -Wall e8asm.c -o e8asm.exe
g++ -m64 -O2 -Wall -lmingw32 e8gui.cpp e8core.cpp -lSDL2main -lSDL2 -o e8gui.exe
