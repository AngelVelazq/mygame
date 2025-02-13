# OBJS specifies the source files
OBJS = src/main.c src/raycasting.c src/game.c

# CC specifies the compiler
CC = gcc

# COMPILER_FLAGS specifies the additional compilation options
COMPILER_FLAGS = -Wall -Wextra -Werror -pedantic -std=gnu99

# LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lm

# OBJ_NAME specifies the name of the executable
OBJ_NAME = raycasting_game

# This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
