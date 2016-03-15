#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <stack>
#include <string>
#include "sudoku_DLX.h"
using namespace std;
// Cell methods
int Cell::cell_value() {return value;}
void Cell::link_row(Cell* l, Cell* r) {
	if (l != NULL)
		l->right = r;
	
	if (r != NULL)
		r->left = l;
}
void Cell::check() {
	value = 1;
}
Cell* Cell::clone() {
	return (new Cell(*this));
}
void Cell::unlink(Cell* c, bool h) {
	if (c != NULL) {
		if (h) {
			c->left->right = c->right;
			c->right->left = c->left;
		}
		else { 
			c->up->down = c->down;
			c->down_up = c->up;
		}
	}
}
void Cell::relink(Cell* c, bool h) {
	if (c!=NULL) {
		if (h) {
			c->left->right = c;
			c->right->left = c;
		}
		else {
			c->up->down = c;
			c->down->up = c;
		} 

	}
}
void Cell::link_column(Cell* u, Cell* d) {
	if (u != NULL)
		u->down = d;		
	if (d != NULL)
		d->up = u;

}
void Cell::go_left(Cell*& c) {
	c = c->left;
}
void Cell::go_right(Cell*& c) {
	c = c->right;
}
void Cell::go_up(Cell*& c) {
	c = c->up;
}
void Cell::go_down(Cell*& c) {
	c = c->down;
}

// EXC GRID
void EXC::initilize(int r, int c, int v) {
	if (v==0) {
		int grid_row = r*81+c*9+v;
	
		for (int i =0; i < 9; ++i){
			// populate cell constraints
			int cell_p = r * 9 + c;
			(grid[grid_row+i][cell_p]).check();
			// populate row constraints
			int row_p = 81 + r * 9+ i;
			//cout << grid_row << endl;
			(grid[grid_row+i][row_p]).check();
			// populate column constraints
			int column_p = 81 * 2 + c * 9 + i;
			(grid[grid_row+i][column_p]).check();
			// populate region constrains
			int region_p = 81 * 3 + (r/3)*27+(c/3)*9 + i;
			(grid[grid_row+i][region_p]).check();
		}
		
	}
	else {
		int grid_row = r*81+c*9+v-1;
		
		// populate cell constraints
		int cell_p = r * 9 + c;
		//cout << cell_p << endl;
		(grid[grid_row][cell_p]).check();

		// populate row constraints
		int row_p = 81 + r * 9+ v -1;
		//cout << row_p << endl;
		(grid[grid_row][row_p]).check();		
		
		// populate column constraints
		int column_p = 81 * 2 + c * 9 + v -1;
		//cout << column_p << endl;
		(grid[grid_row][column_p]).check();
		
		// populate region constrains	
		int region_p = 81 * 3 + (r/3)*27+(c/3)*9 + v - 1;
		//cout << region_p << endl;
		(grid[grid_row][region_p]).check();
	}
	
}

void EXC::linking() {
	Cell* temp =NULL;
	Cell* h[324];
	// linking head cells
	for (int i = 0; i < 324; ++i) {
		if (i==0) {
			Cell::link_row(&nc,&(hc[i]));
		}
		else if (i ==323) {
			Cell::link_row(&hc[i],&nc);
		}
		else {
			Cell::link_row(&(hc[i-1]),&(hc[i]));
		}
		h[i] = &(hc[i]);
	}
	for (int i =0; i < 729; ++i) {
		Cell* f = NULL;
		for (int j =0; j < 324; ++j) {
			if (grid[i][j].cell_value()==1) {
				// link rows
				if (temp !=NULL) {
					Cell::link_row(temp,&(grid[i][j]));
					
				}
				else { 
					f = &(grid[i][j]);
				}
				temp = &(grid[i][j]);
				// link columns
				Cell::link_column(h[j],&(grid[i][j]));
				h[j] = &(grid[i][j]);
							
			}
		}
		Cell::link_row(temp,f);
		temp = NULL;
	}
	for (int i =0 ; i < 324; ++i ) {
		Cell::link_column(h[i],&hc[i]);
	}
	
}
// EXC construct
EXC::EXC(istream& s) {
	string row;
	int i =0;
	while(getline(s,row)) {
		for (int j =0; j < 9; ++j) {
			if (row[j]!='-') {
				initilize(i,j,row[j]-'0');
			}
			else {
				initilize(i,j,0);
			}
		}
		++i;
	}
	linking();
}
EXC::cover(Cell* c) {
	// remove rows
	Cell* t = c;
	for (; t->cell_value()!=-1;Cell::go_down(t)) {
		Cell * t_2 = t;
		Cell::go_right(t_2);
		for (; t_2 != t; Cell::go_right(t_2)) {
			unlink(t_2, false);
		}
	}
	t = c;
	Cell::go_up(t);
	for (; t->cell_value()!=-1 ; Cell::go_down(t)) {
		Cell * t_2 = t;
		Cell::go_right(t_2);
		for (; t_2 != t; Cell::go_right(t_2)) {
			unlink(t_2,false);
		}
	}
}
EXC::uncover(Cell* c) {
	
}
EXC::solve(){
	stack solution;

}


