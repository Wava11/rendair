CC = gcc
CFLAGS_COMMON = -Wall -Wextra -std=c11 `sdl2-config --cflags`
CFLAGS_RELEASE = $(CFLAGS_COMMON) -O2
CFLAGS_DEBUG = $(CFLAGS_COMMON) -g -O0
LDFLAGS = `sdl2-config --libs`

SRC = $(wildcard src/*.c src/**/*.c)
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))
BIN = rendair

# Default to release build
CFLAGS = $(CFLAGS_RELEASE)

all: $(BIN)

debug: CFLAGS = $(CFLAGS_DEBUG)
debug: clean $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(BIN)

.PHONY: all debug clean