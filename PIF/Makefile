CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = main.o board.o fleet.o game.o io.o rnd.o
EXEC = batalha_naval

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)