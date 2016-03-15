CXX        := g++-4.8
CXXFLAGS   := -pedantic -std=c++11 -Wall
LDFLAGS    := -lgtest -lgtest_main -pthread
GCOV       := gcov-4.8
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
VALGRIND   := valgrind

Test: sudoku.h sudoku.c++ sudoku_unitTest.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) -o Test sudoku.c++ sudoku_unitTest.c++ $(LDFLAGS)	