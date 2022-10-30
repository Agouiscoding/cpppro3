SRC_DIR=./src
CXX = gcc
TARGET = test
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

CXXFLAGS= -c -Wall

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^

%.o: %.c
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)