#ifndef _SUDOKU_H
#define _SUDOKU_H
#include <iostream>
#include <stdio.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

class Row_head;
class Column_head;
class Region; 
class Cell {
	public:
		typedef Row_head row;
		typedef Column_head column;
		typedef Region region_p;
	protected:
		int value;
		Cell* left;
		Cell* right;
		Cell* up;
		Cell* down;
		region_p* region;
	
	public:
		Cell(int v =-1, Cell* l = NULL, Cell* r = NULL, Cell* u = NULL, Cell* d = NULL) : value(v), left(l), right(r), up(u), down(d) {}; 
		Cell*& cell_left() { return left;};
		Cell*& cell_right() { return right;};
		Cell*& cell_up() { return up;};
		Cell*& cell_down() { return down;};
		virtual void set_region(Region* r) ;
		virtual char print() ;
		bool check_region(Region* r);
		int cell_value();
		
};
class Row_head : public Cell {
	
	public:
		Row_head(Cell* r = NULL, Cell* u = NULL, Cell* d = NULL): Cell(-1,NULL,r,u,d) {};
		
		void set_region(Region*r) ;
		char print();
};
class Column_head: public Cell {
	public:
		Column_head(Cell* l = NULL, Cell* r = NULL, Cell* d = NULL) : Cell(-1,l,r,NULL,d)  {};
		
		void set_region(Region*r);
		char print();
};

class Region{
	private:
		unordered_map<int,int> contains;
		vector<Cell*> cells;
		// check if inserting the number i is a valid insertion
		bool valid(int i);
	public:	
		
		// check if the whole region is satisfy the requirement
		bool satisfy();
		bool add_cell(Cell* c);

};	

class Sudoku_grid {
	private:
		struct Neutral_Cell: public Cell {

			Neutral_Cell(Cell*r = NULL, Cell* d = NULL) : Cell(-1,NULL,r,NULL,d) {};
			void set_region(Region*r) {
				return;
			}
			char print(){
				return '\0';
			}
		};

	private:
		Cell grid [10][10];
		Neutral_Cell n;
		Row_head rows[9];
		Column_head columns[9];
		Region regions[9];

		void set_cells(istream& w) ;
			
		void cover_row_column(int r, int c);
		void uncover_row_column(int r, int c);
		void cover_region(Region* r);
		void uncover_region(Region* r);
		public:
		Sudoku_grid(istream& w): grid(),n(),rows(),columns(),regions()
		{
			this->set_cells(w);
		};
		void solve();
		void print();
			
};

#endif