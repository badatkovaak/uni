files := $(wildcard *.cpp)
CXX = zig c++
CPPFLAGS = -O3 --std=c++23 -Wall -Wextra -Wpedantic -Wshadow
CXXFLAGS = 


matrix: matrix.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $^ -o $@
	# zig c++ -o $@

