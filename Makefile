CXX        := g++-4.8
CXXFLAGS   := -pedantic -std=c++11 -Wall
LDFLAGS    := -lgtest -lgtest_main -pthread
GCOV       := gcov-4.8
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
VALGRIND   := valgrind

Test: sudoku_DLX.h sudoku_DLX.cpp sudoku_DLX_unitest.cpp
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) -o Test sudoku_DLX.cpp sudoku_DLX_unitest.cpp $(LDFLAGS)	
Run_Test: Test
	$(VALGRIND) ./Test
Clean: *.gcda *.gcno Test
	rm *.gcda
	rm Test
	rm *.gcno
