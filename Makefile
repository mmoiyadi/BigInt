# Makefile for BigInt
CXX		 = g++
CXXFLAGS = -Wall -pthread -std=c++11
TARGET	 = test_big_int
SRC		 = big_int.cpp test_big_int.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)