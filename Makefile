CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=gnu99
LDFLAGS = -L./venv_sdl2/lib -Wl,-rpath,./venv_sdl2/lib -lSDL2 -lm
INCLUDES = -I./venv_sdl2/include

SRC = src/main.c src/raycasting.c src/game.c
OBJ = $(SRC:.c=.o)
TARGET = raycasting_game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LDFLAGS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

re: clean all
