all:
	gcc -Isrc/include -Lsrc/lib -o main src/lib/main.c src/lib/snake.c src/lib/grid.c src/lib/setup.c src/lib/scene_manager.c src/lib/graphics.c -lmingw32 -lSDL2main -lSDL2