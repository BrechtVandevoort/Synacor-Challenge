#Author: Brecht Vandevoort

NAME = synacor
BIN = bin/
SRC = src/

CC = gcc
FLAGS = -Wall -pedantic
COMMANDFLAGS = 
CFLAGS = -c $(FLAGS) $(COMMANDFLAGS)
LFLAGS = $(FLAGS) $(COMMANDFLAGS)

EXEC = $(BIN)$(NAME)
CFILES = $(shell find $(SRC) -name *.c)
HEADERS = $(shell find $(SRC) -name *.h)
OBJS = $(CFILES:$(SRC)%.c=$(BIN)%.o)

all: compile

run: $(EXEC)
	./$(EXEC) ./info/challenge.bin
	
compile: $(EXEC)

$(EXEC): $(OBJS) $(HEADERS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXEC)

$(BIN)%.o: $(SRC)%.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(BIN)*.o $(EXEC)
