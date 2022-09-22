gcc -static -m64 -O2 -Wall e8asm.c -o e8asm.exe
g++ -static-libgcc -static-libstdc++ -m64 -O2 -Wall -lmingw32 euler8.cpp e8core.cpp -lSDL2main -lSDL2 -Wl,-subsystem,windows -o euler8.exe
