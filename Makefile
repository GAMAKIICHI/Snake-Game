all:
	gcc -Isrc/include -Lsrc/lib -o main src/main.c -lmingw32 -lSDL2main -lSDL2