#Compile
CC = gcc
CFLAGS = -Wall -Werror -fPIC -Iinclude  -fsanitize=address
#Include, hogy a main leforduljon

#Folders
SRC_DIR = src
INCLUDE_DIR= include
LIB_DIR = lib
BIN_DIR = bin
OBJ_DIR = obj

#Main bin
EXEC_NAME = main

#Configure 
LIB_NAME = libtesselix.a

#Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
#Out files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#Build
all: $(LIB_DIR)/$(LIB_NAME)

# $@ = lib/libtesselix.a 
$(LIB_DIR)/$(LIB_NAME): $(OBJS)
	mkdir -p $(LIB_DIR)
	ar rcs $@ $(OBJS)

# .c fájlok -> .o fájlok, feltételekkel
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

#main.c
$(BIN_DIR)/$(EXEC_NAME): main.c $(LIB_DIR)/$(LIB_NAME)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -L$(LIB_DIR) -ltesselix -o $(BIN_DIR)/$(EXEC_NAME)  main.c

#Clean
clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR)/*.a $(BIN_DIR)/$(EXEC_NAME)