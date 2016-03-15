#include <iostream>
#include <stdio.h>
#include <unordered_map>
#include <string>
#include "sudoku.h"
int main () {
	Sudoku_grid s(cin);
	s.print();
	s.solve();
	s.print();
	return 0;
}