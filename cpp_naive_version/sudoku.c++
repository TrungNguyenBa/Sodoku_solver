#include <iostream>
#include <stdio.h>
#include <unordered_map>
#include <string>
#include "sudoku.h"
using namespace std;

// CELL METHODS
void Cell::set_region(Region* r) {
			region = r;
		}
char Cell::print() {
			if (value ==0){
				return '-';
			}
			return value+'0';
}
bool Cell::check_region(Region* r){
	if (region ==r) {
		return true;
	}
	else
		return false;
}
int Cell::cell_value(){
	return value;
}

// ROW_HEAD METHODS
void Row_head::set_region(Region*r) {
			return;
		}
char Row_head::print(){
			return '\0';
}

// Column_head Methods
void Column_head::set_region(Region*r) {
	return;
}
char Column_head::print(){
	return '\0';
}

//REGION Methods
bool Region::valid(int i) {	
	if ((contains.find(i) == contains.end())||(i==0)) {
		contains[i] =1;
		return true;
	}
	else {
		return false;
	}
}
// check if the whole region is satisfy the requirement
bool Region::satisfy(){
	if (contains.size()!= 9 && contains.size()!=10) {
		return false;
	} 
	for (int i =1; i < 10; i++){
		if (contains.find(i) == contains.end()) {
			cout << i << endl;
			return false;
		}
	}
	return true;
}
bool Region::add_cell(Cell* c){
	if (valid(c->cell_value())) {
		cells.push_back(c);
		c->set_region(this);
		return true;
	}
	else {
		return false;
	}
}		

//Sudoku_grid Methods
void Sudoku_grid::set_cells(istream& w) {
			string s;
			n = Neutral_Cell(&(columns[0]),&(rows[0]));
			for (int i = 0; i < 9; ++i  ) {
				if (i ==0) {
					rows[i] = Row_head(&(grid[i][0]),&n,&(rows[i+1]));
				}
				rows[i] = Row_head(&(grid[i][0]),&(rows[i-1]),&(rows[i+1]));
			}
			for (int i = 0; i < 9; ++i  ) {
				if (i ==0) {
					columns[i] = Column_head(&n,&(columns[i+1]),&(grid[0][i]));
				}
				columns[i] = Column_head(&(columns[i-1]),&(columns[i+1]),&(grid[0][i]));
			}
			int i =0;
			while (getline(w,s)&&(i<9)){
				for (int j =0 ; j < 9; ++j) {
					int  v =0;
					if (s[j]!='-'){
							v = s[j] -'0';
					}
					if ( i < 3 && j < 3) {
						if (i==0 && j ==0) {
							grid[i][j]= Cell(v,&(rows[i]),&(grid[i][j+1]),&(columns[j]),&(grid[i+1][j]));
						}
						else if (i==0&& j!=0){
							grid[i][j]= Cell(v,&(grid[i][j-1]),&(grid[i][j+1]),&(columns[j]),&(grid[i+1][j]));
						}
						else if (j==0 && i!=0){
							grid[i][j]= Cell(v,&(rows[i]),&(grid[i][j+1]),&(grid[i-1][j]),&(grid[i+1][j]));
						}
						else 
							grid[i][j]= Cell(v,&(grid[i][j-1]),&(grid[i][j+1]),&(grid[i-1][j]),&(grid[i+1][j]));
						assert(regions[0].add_cell(&(grid[i][j])));
					}
					else if (i  < 3 && j >=3 && j < 6) {
						if (i==0){
							grid[i][j]= Cell(v,&(grid[i][j-1]),&(grid[i][j+1]),&(columns[j]),&(grid[i+1][j]));
						}
						else { 
							grid[i][j]= Cell(v,&(grid[i][j-1]),&(grid[i][j+1]),&(grid[i-1][j]),&(grid[i+1][j]));
						}
						assert(regions[1].add_cell(&(grid[i][j])));
					}
					else if (i < 3 && j >= 6) {
						
						if (i==0){
							grid[i][j]= Cell(v,&(grid[i][j-1]),&(grid[i][j+1]),&(columns[j]),&(grid[i+1][j]));
						}
						else {
							grid[i][j]= Cell(v,&(grid[i][j-1]),&(grid[i][j+1]),&(grid[i-1][j]),&(grid[i+1][j]));
						}
						assert(regions[2].add_cell(&(grid[i][j])));
					}
					else if ( i >=3 && i<6 && j <3 ){
						
						if (j==0){
							grid[i][j]= Cell(v,&(rows[i]),&(grid[i][j+1]),&(grid[i-1][j]),&(grid[i+1][j]));
						}
						else 
							grid[i][j]= Cell(v,&(grid[i][j-1]),&(grid[i][j+1]),&(grid[i-1][j]),&(grid[i+1][j]));
						assert(regions[3].add_cell(&(grid[i][j])));
					}
					else if ( i >=3 &&  i <6 && j >=3 && j < 6 ) {
						
						grid[i][j]= Cell(v,&(grid[i][j-1]),&(grid[i][j+1]),&(grid[i-1][j]),&(grid[i+1][j]));
						assert(regions[4].add_cell(&(grid[i][j])));
					}
					else if ( i >=3 && i< 6 && j >= 6 ) {
						
						grid[i][j]= Cell(v,&(grid[i][j-1]),&(grid[i][j+1]),&(grid[i-1][j]),&(grid[i+1][j]));
						assert(regions[5].add_cell(&(grid[i][j])));
					}
					else if ( i >=6 && j <3 ) {
						if (j==0){
							grid[i][j]= Cell(v,&(rows[i]),&(grid[i][j+1]),&(grid[i-1][j]),&(grid[i+1][j]));
						}
						else {
							grid[i][j]= Cell(v,&(grid[i][j-1]),&(grid[i][j+1]),&(grid[i-1][j]),&(grid[i+1][j]));
						}
						assert(regions[6].add_cell(&(grid[i][j])));
					}
					else if ( i >=6 && j >=3 && j < 6 ) {	
						
						grid[i][j]= Cell(v,&(grid[i][j-1]),&(grid[i][j+1]),&(grid[i-1][j]),&(grid[i+1][j]));
						assert(regions[7].add_cell(&(grid[i][j])));
					}
					else if ( i >=6 && j >=6 ) {
						
						grid[i][j]= Cell(v,&(grid[i][j-1]),&(grid[i][j+1]),&(grid[i-1][j]),&(grid[i+1][j]));
						assert(regions[8].add_cell(&(grid[i][j])));
					}

				}
				++i;
			}
			for(int k =0; k < 9; k++) {
				grid[k][9] = Cell(-1,&(grid[k][8]),NULL,NULL,NULL);
			}
			for(int t=0;t<9;t++) {
				grid[9][t] = Cell(-1,NULL,NULL,&(grid[8][t]),NULL);
			}

}
void Sudoku_grid::cover_row_column(int r, int c) {
	Cell * i = &(grid[r][c]);
	for (Cell* t = i->cell_left(); t->cell_value() != -1; t = t->cell_left()) {
		t->cell_up()->cell_down() = t->cell_down();
		t->cell_down()->cell_up() = t->cell_up();
	}
	for (Cell* t = i->cell_right(); t->cell_value() != -1; t = t->cell_right()) {
		t->cell_up()->cell_down() = t->cell_down();
		t->cell_down()->cell_up() = t->cell_up();
	}
	for (Cell* t = i->cell_up(); t->cell_value() != -1; t = t->cell_up()) {
		t->cell_left()->cell_right() = t->cell_right();
		t->cell_right()->cell_left() = t->cell_left();
	}
	for (Cell* t = i->cell_down(); t->cell_value() != -1; t = t->cell_down()) {
		t->cell_left()->cell_right() = t->cell_right();
		t->cell_right()->cell_left() = t->cell_left();
	}
}
void Sudoku_grid::uncover_row_column(int r, int c) {
	Cell * i = &(grid[r][c]);
	for (Cell* t = i->cell_left(); t->cell_value() != -1; t = t->cell_left()) {
		t->cell_up()->cell_down() = t;
		t->cell_down()->cell_up() = t;
	}
	for (Cell* t = i->cell_right(); t->cell_value() != -1; t = t->cell_right()) {
		t->cell_up()->cell_down() = t;
		t->cell_down()->cell_up() = t;
	}
	for (Cell* t = i->cell_up(); t->cell_value() != -1; t = t->cell_up()) {
		t->cell_left()->cell_right() = t;
		t->cell_right()->cell_left() = t;
	}
	for (Cell* t = i->cell_down(); t->cell_value() != -1; t = t->cell_down()) {
		t->cell_left()->cell_right() = t;
		t->cell_right()->cell_left() = t;
	}
}
void Sudoku_grid::cover_region(Region* r ) {

}
void Sudoku_grid::uncover_region(Region* r ) {
	
}
void Sudoku_grid::solve() {
}
void Sudoku_grid::print(){
	for (int i =0; i <9; i++){
		for (int j =0; j< 9; j++) {
			cout << grid[i][j].print() <<" | ";
		}
		cout << endl;
		cout <<"___________________________________" <<endl;
	}
}
