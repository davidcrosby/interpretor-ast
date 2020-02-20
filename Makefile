GPPWARN     = -Wall -Wextra -Wpedantic -Wshadow -Wold-style-cast
GPPOPTS     = ${GPPWARN}
CC  				= g++ -std=c++17 -g -O0 ${GPPOPTS}
EXEC_TARGET = main
ENTRY_OBJECT= $(EXEC_TARGET).o
OBJ_FILES   = token.o scanner.o error_handler.o parser.o

TEST_DIR	  = test
TEST_EXEC_TARGET = test
TEST_ENTRY_OBJECT= $(TEST_DIR)/$(TEST_EXEC_TARGET).o
TEST_OBJ	  = $(TEST_DIR)/scanner_test.o
TEST_ALL_OBJECTS = $(OBJ_FILES) $(TEST_OBJ) $(TEST_ENTRY_OBJECT)


all: $(EXEC_TARGET)

test: $(TEST_ALL_OBJECTS)
	$(CC) -o $(TEST_DIR)/$@ $^

%.o: %.cpp
	$(CC) -c -o $@ $<

$(EXEC_TARGET): $(OBJ_FILES) $(ENTRY_OBJECT)
	$(CC) -o $@ $^

clean:
	rm $(OBJ_FILES) $(TEST_OBJ)

spotless: clean
	rm $(EXEC_TARGET) $(TEST_ALL_OBJECTS)
