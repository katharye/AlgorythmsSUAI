CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

TARGET = all_labs

SRC_DIR = src
BUILD_DIR = build

SRCS = src/main.c src/lab1/lab1_alg.c src/lab2/lab2_alg.c src/lab3/lab3_alg.c src/lab4/lab4_alg.c src/lab5/lab5_alg.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild
