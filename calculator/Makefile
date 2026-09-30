CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -lm
TARGET=calculator

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

clean:
	rm -f $(TARGET)