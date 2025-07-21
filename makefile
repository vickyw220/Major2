CC = gcc
CFLAGS = -Wall
OBJ = newshell.o builtins.o pipeline.o history.o

newshell: $(OBJ)
	$(CC) $(CFLAGS) -o newshell $(OBJ)

clean:
	rm -f *.o newshell
