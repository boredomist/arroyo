SRC := $(shell find src -name "*.c")
OBJ := $(SRC:.c=.o)

CC  := gcc

LFLAGS := -lreadline -lm
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c99 -ggdb -O0 -Wno-unused -Wno-unused-parameter -Iinclude/

all: $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o arroyo

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)

check-syntax:
	$(CC) -o nul $(CFLAGS) -S $(CHK_SOURCES)
