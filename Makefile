# Compiler
CC = gcc

# Flags (show all warns)
CFLAGS = -Wall

# Compile all C files
SRCS = main.c uilib.c db.c paciente.c list.c

# Object files (replace .c with .o)
OBJS = $(SRCS:.c=.o)

# Test files
TEST_SRCS = test.c uilib.c db.c paciente.c list.c
TEST_OBJS = $(TEST_SRCS:.c=.o)

# Executable names
TARGET = healthsys
TEST_TARGET = test_program

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Link test object files to create test executable
$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Run valgrind on test
valgrind: $(TEST_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_TARGET)
	$(MAKE) clean

# Quick valgrind (less verbose)
memcheck: $(TEST_TARGET)
	valgrind --leak-check=full ./$(TEST_TARGET)
	$(MAKE) clean

# Explicit compile target (produces the target program)
compile: $(TARGET)

# Default target (compile and run)
all: compile run

# Clean up
clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)

# Phony targets (not files) to avoid conflicts with files of the same name
.PHONY: all compile run clean test valgrind memcheck