CXX := g++
CXXFLAGS := -Wall -Werror -Wextra -pedantic -std=c++23 -march=native -O3

TARGET := encryptor

SRC := src/mainexample.cpp src/MatrixEncryptor.cpp
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)
