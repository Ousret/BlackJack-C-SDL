CC  = gcc -Wall
BIN = BlackJack
INC = includes/
CFLAGS =`sdl-config --libs --cflags` -lSDL_image -lSDL_ttf -lSDL_mixer

$(BIN): main.o BlackJack.o STJ_SDL.o
	$(CC) main.o BlackJack.o STJ_SDL.o -o $(BIN) -lm $(CFLAGS)

main.o: main.c $(INC)BlackJack.h $(INC)STJ_SDL.h
	$(CC) -c main.c $(CFLAGS)
	
BlackJack.o: BlackJack.c $(INC)BlackJack.h
	$(CC) -c BlackJack.c $(CFLAGS)
	
STJ_SDL.o: STJ_SDL.c $(INC)STJ_SDL.h $(INC)BlackJack.h
	$(CC) -c STJ_SDL.c $(CFLAGS)

clean:
	@rm -f *.o
	@rm $(BIN)