CC = gcc
CFLAGS = -Wall
TARGET = pacman.exe 
SRCS = main.c 
LIBS = -lraylib -lm -lpthread -ldl -lrt -lX11

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBS) -o $(TARGET)

clean:	
	rm -f $(TARGET)