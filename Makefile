files := $(wildcard *.cpp)
CXX = clang++
CPPFLAGS = -O3 --std=c++20 -Wall -Wextra -Wpedantic -Wshadow
CXXFLAGS = 


matrix: matrix.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $^ -o ./target/matrix

