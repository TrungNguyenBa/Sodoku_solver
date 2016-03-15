#ifndef _SUDOKU_DLX_H
#define _SUDOKU_DLX_H
#include <iostream>
#include <stdio.h>
#include <cstdlib>
//using namespace std;
class Cell {
	protected:
		int value;
		Cell* left;
		Cell* right;
		Cell* up;
		Cell* down;	
	public:
		Cell(int v = 0, Cell* l = NULL, Cell* r = NULL, Cell* u = NULL, Cell* d = NULL) : value(v),left(l),right(r),up(u),down(d) {};
		int cell_value() ;
		void check();
		Cell* clone();
		static void link_row(Cell* l, Cell* r) ;
		static void link_column(Cell* u, Cell* d);
		static void unlink(Cell * c, bool horizontal);
		static void relink(Cell * c, bool horizontal;
		static void go_left(Cell*& c);
		static void go_right(Cell*& c);
		static void go_up(Cell*& c);
		static void go_down(Cell*& c);
};
class Neutral_cell : public Cell {
	public:
		Neutral_cell(Cell* r =NULL) : Cell(-1,NULL,r,NULL,NULL) {};
};
class Head_cell : public Cell {
	public:
		Head_cell(Cell* l = NULL, Cell* r = NULL, Cell* d = NULL)  : Cell(-1,l,r,NULL,d) {};
};


class EXC {
	private:
		class Grid {
			private:
				class Cell_Handle {
					private:
						Cell* p[324] ;
					public:
						Cell_Handle() {
							for (int i = 0; i < 324; ++i) {
								p[i] = new Cell();
							} 
						};
						Cell& operator [] (int i) {
							return *(p[i]);
						}
						~Cell_Handle() {
							for (int i =0 ; i < 324; ++i ) {
								delete(p[i]);
							}
						}

				};
			private:
				Cell_Handle* g[729];
			public:
				Grid() {
					for (int i =0; i < 729; ++i) {
						g[i] = new Cell_Handle();
					}
				}
				Cell_Handle& operator [] (int i) {
					return *(g[i]);
				}
				~Grid() {
					for(int i = 0 ; i < 729; ++i) {
						delete(g[i]);
					}
				}

		};
	private:
		Neutral_cell nc;
		Grid grid;
		Head_cell hc[324];
		// testing purpose only
		EXC() {}; 
		void initilize(int r, int c, int v);
		void linking();
		void cover(Cell*  c);
		void uncover(Cell* c);
	public:
		EXC(std::istream& s);
		void solve();
		void print();
		
};
#endif	