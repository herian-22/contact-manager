CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags glib-2.0 gobject-2.0`
LDFLAGS = `pkg-config --libs glib-2.0 gobject-2.0`
SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/contact_manager

SRCS = $(wildcard $(SRC_DIR)/*.c) 
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all clean

