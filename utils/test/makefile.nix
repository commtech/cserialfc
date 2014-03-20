SHELL = /bin/sh
TARGET = test

SRCS = $(shell echo *.c)
HEADERS = ../../src/
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -I $(HEADERS)
LDFLAGS = -L../../ -lcserialfc

CC = gcc

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(TARGET)

clean:
	rm src/*.o
