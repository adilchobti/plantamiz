# Makefile Windows-only (MinGW / gcc)

CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -Wpedantic -Isrc
LDFLAGS =

EXE = plantamitz.exe

SRC = src/main.c \
      src/game.c src/board.c src/match.c src/input.c \
      src/platform.c src/utils.c src/save.c src/contracts.c

OBJ = $(SRC:.c=.o)

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q $(OBJ) $(EXE) 2> NUL || exit 0

.PHONY: all clean
