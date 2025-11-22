CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`

SRC = $(wildcard src/*.c src/**/*.c)
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))
BIN = rendair

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(BIN)

.PHONY: all clean