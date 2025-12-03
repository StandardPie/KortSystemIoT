CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
TARGET = card_system
SOURCES = main.c input.c card_system.c door_control.c
HEADERS = input.h card_system.h door_control.h
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) cards.dat

.PHONY: clean0