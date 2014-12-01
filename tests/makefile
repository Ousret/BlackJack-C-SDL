CC = gcc -I/opt/local/include/ -L/opt/local/lib
BIN = bj_tests
CFLAGS = -lcunit
INC = includes/

$(BIN): cunit.o bj_engine.o
	$(CC) cunit.o bj_engine.o -o $(BIN) -lm $(CFLAGS)

cunit.o: cunit.c $(INC)bj_engine.h
	$(CC) -c cunit.c $(CFLAGS)

bj_engine.o: bj_engine.c $(INC)bj_engine.h
	$(CC) -c bj_engine.c $(CFLAGS)

clean:
	@rm ­f *.o
	@rm $(BIN)