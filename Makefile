CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

# Имя итогового файла
TARGET = all_labs

# Папки
SRC_DIR = src
BUILD_DIR = build

# Ищем все .c файлы рекурсивно в папке src
# Либо можно оставить жесткий список: SRCS = src/main.c src/lab1/lab1_alg.c ...
SRCS = src/main.c src/lab1/lab1_alg.c src/lab2/lab2_alg.c src/lab3/lab3_alg.c src/lab4/lab4_alg.c src/lab5/lab5_alg.c

# Превращаем src/file.c -> build/src/file.o
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Основная цель
all: $(TARGET)

# Линковка (сборка финального бинарника)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Компиляция каждого файла
# | $(BUILD_DIR) означает "order-only prerequisite":
# папка должна существовать, но ее обновление не вызывает пересборку
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Пересборка
rebuild: clean all

.PHONY: all clean rebuild
