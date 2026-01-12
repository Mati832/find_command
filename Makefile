CC = gcc
# Hinzugefügt: -pthread für die Kompilierung
CFLAGS = -Iinclude -Wall -Wextra -g -pthread
# Hinzugefügt: -pthread für das Linken
LDFLAGS = -pthread

SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = obj
TARGET = findClone
TEST_TARGET = run_tests

# Produktive Logik (Filter, Queue, etc.)
LOGIC_SRCS = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
LOGIC_OBJS = $(LOGIC_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Hauptprogramm
MAIN_OBJ = $(OBJ_DIR)/main.o

# Testprogramm (Sammelt alle .c Dateien aus /tests)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(TARGET)

# Linken des Hauptprogramms (nutzt LDFLAGS)
$(TARGET): $(LOGIC_OBJS) $(MAIN_OBJ)
	$(CC) $^ -o $(TARGET) $(LDFLAGS)

# Linken des Testprogramms (nutzt LDFLAGS)
$(TEST_TARGET): $(LOGIC_OBJS) $(TEST_OBJS)
	$(CC) $^ -o $(TEST_TARGET) $(LDFLAGS)

# Regel für Objekte aus src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regel für Objekte aus tests/
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_TARGET)
	@./$(TEST_TARGET)
	@# rm -f $(TEST_TARGET)  <-- Tipp: Lass es zum Debuggen kurz da, falls ein Test crasht

clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TEST_TARGET)
	rm -rf test_root

.PHONY: all clean test
