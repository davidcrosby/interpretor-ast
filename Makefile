GPPWARN     = -Wall -Wextra -Wpedantic -Wshadow -Wold-style-cast
GPPOPTS     = ${GPPWARN}
CC  				= g++ -std=c++17 -g -O0 ${GPPOPTS}
EXEC_TARGET = lox
OBJ_FILES   = token.o main.o scanner.o

all: $(EXEC_TARGET)

%.o: %.cpp
	$(CC) -c -o $@ $<

$(EXEC_TARGET): $(OBJ_FILES)
	$(CC) -o $@ $^

clean:
	rm $(OBJ_FILES)

spotless: clean
	rm $(EXEC_TARGET)
