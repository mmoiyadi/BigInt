# Makefile for BigInt
CXX		 = g++
CXXFLAGS = -Wall -std=c++11
TARGET	 = test_big_int
SRC		 = test_big_int.cpp big_int.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)