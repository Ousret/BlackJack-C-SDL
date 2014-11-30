CC  = gcc -Wall
BIN = BlackJack
INC = includes/
CFLAGS =`sdl-config --libs --cflags` -lSDL_image -lSDL_ttf -lSDL_mixer
CSDL = `sdl-config --libs --cflags`

$(BIN): main.o bj_engine.o STJ_SDL.o
	$(CC) main.o bj_engine.o STJ_SDL.o -o $(BIN) -lm $(CFLAGS)

main.o: main.c $(INC)bj_engine.h $(INC)STJ_SDL.h
	$(CC) -c main.c $(CSDL)
	
bj_engine.o: bj_engine.c $(INC)bj_engine.h
	$(CC) -c bj_engine.c $(CSDL)
	
STJ_SDL.o: STJ_SDL.c $(INC)STJ_SDL.h $(INC)bj_engine.h
	$(CC) -c STJ_SDL.c $(CSDL)

clean:
	@rm -f *.o
	@rm $(BIN)