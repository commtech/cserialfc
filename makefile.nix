SHELL = /bin/sh
TARGET = libcserialfc.so

SRCS = $(shell echo src/*.c)
HEADERS = $(shell echo src/*.h)
OBJS = $(SRCS:.c=.o)

CFLAGS = -fPIC -Wall -Wextra -m64
LDFLAGS = -shared

CC = gcc

all: $(TARGET)

$(TARGET): $(HEADERS) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(HEADERS) $(OBJS) -o $(TARGET) -lm

clean:
	rm src/*.o
	rm *.so
