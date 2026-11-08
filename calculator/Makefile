CXX=g++
CXXFLAGS=-Wall -Wextra -std=c++11
TARGET=calculator

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp -lm

clean:
	rm -f $(TARGET)