#Author: Brecht Vandevoort

NAME = synacor
BIN = bin/
SRC = src/

CC = gcc
FLAGS = -Wall -pedantic
CFLAGS = -c $(FLAGS)
LFLAGS = $(FLAGS)

EXEC = $(BIN)$(NAME)
CFILES = $(shell find $(SRC) -name *.c)
HEADERS = $(shell find $(SRC) -name *.h)
OBJS = $(CFILES:$(SRC)%.c=$(BIN)%.o)

all: run

run: $(EXEC)
	./$(EXEC) ./info/challenge.bin
	
compile: $(EXEC)

$(EXEC): $(OBJS) $(HEADERS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXEC)

$(BIN)%.o: $(SRC)%.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(BIN)*.o $(EXEC)
