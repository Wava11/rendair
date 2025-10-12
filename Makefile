CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
BIN = rendair

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(BIN)
