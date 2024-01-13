all:
	gcc -Isrc/include -Lsrc/lib -o main src/lib/main.c src/lib/linkedlist.c src/lib/snake.c src/lib/grid.c -lmingw32 -lSDL2main -lSDL2