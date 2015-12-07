#Author: Brecht Vandevoort

EXEC = synacor
BIN = bin/
SRC = src/

CC = gcc
FLAGS = -Wall -pedantic
CFLAGS = -c $(FLAGS)
LFLAGS = $(FLAGS)

CFILES = $(shell find $(SRC) -name *.c)
HEADERS = $(shell find $(SRC) -name *.h)
OBJS = $(CFILES:$(SRC)%.c=$(BIN)%.o)

all: $(EXEC)

$(EXEC): $(OBJS) $(HEADERS)
	$(CC) $(LFLAGS) $(OBJS) -o $(BIN)$(EXEC)

$(BIN)%.o: $(SRC)%.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(BIN)*.o $(BIN)$(EXEC)
