CC  = gcc -Wall -Wextra
BIN = BlackJack
INC = includes/
CFLAGS =`sdl-config --libs --cflags` -lSDL_image -lSDL_ttf -lfmodex -lESDL #-lGL -lGLU -lGLEW -lSDL2_gpu 
CSDL = `sdl-config --cflags`

$(BIN): main.o bj_engine.o
	$(CC) main.o bj_engine.o -o $(BIN) -lm $(CFLAGS)

main.o: main.c $(INC)bj_engine.h
	$(CC) -c main.c $(CSDL)
	
bj_engine.o: bj_engine.c $(INC)bj_engine.h
	$(CC) -c bj_engine.c

clean:
	@rm -f *.o
	@rm $(BIN)