TARGET = gc-compress
BUILD_DIR = build

CC = gcc
CFLAGS = -g -Wall -Werror

all: dir $(TARGET)

$(TARGET): main.o rle.o
	$(CC) $(CFLAGS) $(BUILD_DIR)/main.o $(BUILD_DIR)/rle.o -o $(BUILD_DIR)/$(TARGET)

main.o: main.c rle.h
	$(CC) $(CFLAGS) -c main.c -o $(BUILD_DIR)/main.o

rle.o: rle.c rle.h
	$(CC) $(CFLAGS) -c rle.c -o $(BUILD_DIR)/rle.o

dir:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)