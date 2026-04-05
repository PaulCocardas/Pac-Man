CC = gcc
CFLAGS = -Wall 
TARGET = pacman.exe

SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)

LIBS = -lraylib -lm -lpthread -ldl -lrt -lX11

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)