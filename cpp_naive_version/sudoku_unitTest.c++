#include <iostream> // cout, endl
#include <sstream>  // ostringstream
#include <string>	// string
#include <utility>	// pair

#include "gtest/gtest.h"
#define private public
#define protected public
#include "sudoku.h"
#define private private
#define protected protected
using namespace std;
TEST(row_linking,row_linking_1){
	istringstream w("---------\n---------\n---------\n---------\n---------\n---------\n---------\n---------\n---------\n");
	Sudoku_grid grid(w);
	ASSERT_EQ(grid.rows[0].cell_value(),-1);
	int t =0;
	for(Cell* i = grid.rows[0].right; i->cell_value() != -1; i = i->right){
		ASSERT_EQ(i->cell_value(),0);
		++t;
	}
	ASSERT_EQ(9,t);
}
TEST(row_linking,row_linking_2){
	istringstream w("---------\n---------\n---------\n123456789\n---------\n---------\n---------\n---------\n---------\n");
	Sudoku_grid grid(w);
	int k =1;
	Cell* i;
	for(i = grid.rows[3].right; i->cell_value() != -1; i = i->right){
		ASSERT_EQ(k,i->cell_value());
		++k;
	}

	ASSERT_EQ(10,k);
	k =9;
	for(i = i->left;i->cell_value() != -1;i=i->left) {
		ASSERT_EQ(k,i->cell_value());
		--k;	
	}
}
TEST(column_linking,column_linking_1){
	istringstream w("---------\n---------\n---------\n---------\n---------\n---------\n---------\n---------\n---------\n");
	Sudoku_grid grid(w);
	ASSERT_EQ(grid.columns[0].cell_value(),-1);
	int t =0;
	for(Cell* i = grid.columns[0].down; i->cell_value() != -1; i = i->down){
		ASSERT_EQ(i->cell_value(),0);
		++t;
	}
	ASSERT_EQ(9,t);
}
TEST(column_linking,column_linking_2){
	istringstream w("1--------\n2--------\n3--------\n4--------\n5--------\n6--------\n7--------\n8--------\n9--------\n");
	Sudoku_grid grid(w);
	int k =1;
	Cell* i;
	for(i = grid.columns[0].down; i->cell_value() != -1; i = i->down){
		ASSERT_EQ(i->cell_value(),k);
		++k;
	}
	ASSERT_EQ(10,k);
	k =9;
	for(i = i->up;i->cell_value() != -1;i=i->up) {
		ASSERT_EQ(i->cell_value(),k);
		--k;	
	}
}
TEST(region_linking,region_linking_1){
	istringstream w("123------\n456------\n789------\n---------\n---------\n---------\n---------\n---------\n---------\n");
	Sudoku_grid grid(w);
	ASSERT_EQ(true,grid.regions[0].satisfy()); 
}
TEST(region_linking,region_linking_2){
	istringstream w("---123---\n---456---\n---789---\n---------\n---------\n---------\n---------\n---------\n---------\n");
	Sudoku_grid grid(w);
	for (int i =0; i < 9; ++i) {
		ASSERT_EQ(i+1,(grid.regions[1].cells.at(i))->cell_value());
	}
	ASSERT_EQ(true,grid.regions[1].satisfy());
}
TEST(world_linking,world_linking_1){
	istringstream w("123456789\n456789123\n789123456\n---------\n---------\n---------\n---------\n---------\n---------\n");
	Sudoku_grid grid(w);
	Cell* t = grid.rows[0].right; 
	for (int i =0; i < 9 ; i++){
		ASSERT_EQ(i+1,t->cell_value());
		t = t->right; 
	}
	t = t->left;
	for (int i =9; i > 0 ; i--){
		ASSERT_EQ(i,t->cell_value());
		t = t->left; 
	}
	t = grid.rows[1].right;
	for (int i =0; i < 6 ; i++){
		ASSERT_EQ(i+4,t->cell_value());
		t = t->right;
	}
	t = t->left;
	for (int i =6; i > 0 ; i--){
		ASSERT_EQ(i+3,t->cell_value());
		t = t->left; 
	}
	t = &(grid.grid[2][3]);
	for (int i = 0; i < 6 ; i++ ) {
		ASSERT_EQ(i+1,t->cell_value());
		t = t->right;
	}
	ASSERT_EQ(true,grid.regions[0].satisfy());
	ASSERT_EQ(true,grid.regions[1].satisfy());
	ASSERT_EQ(true,grid.regions[2].satisfy());
}
TEST(world_linking,world_linking_2){
	istringstream w("147------\n258------\n369------\n471------\n582-----\n693------\n714-------\n825------\n936------\n");
	Sudoku_grid grid(w);
	Cell* t = grid.columns[0].down; 
	for (int i =0; i < 9 ; i++){
		ASSERT_EQ(i+1,t->cell_value());
		t = t->down; 
	}
	t = t->up;
	for (int i =9; i > 0 ; i--){
		ASSERT_EQ(i,t->cell_value());
		t = t->up; 
	}
	t = grid.columns[1].down;
	for (int i =0; i < 6 ; i++){
		ASSERT_EQ(i+4,t->cell_value());
		t = t->down;
	}
	t = t->up;
	for (int i =6; i > 0 ; i--){
		ASSERT_EQ(i+3,t->cell_value());
		t = t->up; 
	}
	t = &(grid.grid[3][2]);
	for (int i = 0; i < 6 ; i++ ) {
		ASSERT_EQ(i+1,t->cell_value());
		t = t->down;
	}
	ASSERT_EQ(true,grid.regions[0].satisfy());
	ASSERT_EQ(true,grid.regions[3].satisfy());
	ASSERT_EQ(true,grid.regions[6].satisfy());
}
TEST(world_linking,world_linking_3){
	istringstream w("---------\n---------\n---------\n123456789\n456789123\n789123456\n---------\n---------\n---------\n");
	Sudoku_grid grid(w);
	Cell* t = grid.rows[3].right; 
	for (int i =0; i < 9 ; i++){
		ASSERT_EQ(i+1,t->cell_value());
		t = t->right; 
	}
	t = t->left;
	for (int i =9; i > 0 ; i--){
		ASSERT_EQ(i,t->cell_value());
		t = t->left; 
	}
	t = grid.rows[4].right;
	for (int i =0; i < 6 ; i++){
		ASSERT_EQ(i+4,t->cell_value());
		t = t->right;
	}
	t = t->left;
	for (int i =6; i > 0 ; i--){
		ASSERT_EQ(i+3,t->cell_value());
		t = t->left; 
	}
	t = &(grid.grid[5][3]);
	for (int i = 0; i < 6 ; i++ ) {
		ASSERT_EQ(i+1,t->cell_value());
		t = t->right;
	}
	ASSERT_EQ(true,grid.regions[3].satisfy());
	ASSERT_EQ(true,grid.regions[4].satisfy());
	ASSERT_EQ(true,grid.regions[5].satisfy());
	
}
TEST(world_linking,world_linking_4){
	istringstream w("---------\n---------\n---------\n---------\n---------\n---------\n123456789\n456789123\n789123456\n");
	Sudoku_grid grid(w);
	Cell* t = grid.rows[6].right; 
	for (int i =0; i < 9 ; i++){
		ASSERT_EQ(i+1,t->cell_value());
		t = t->right; 
	}
	t = t->left;
	for (int i =9; i > 0 ; i--){
		ASSERT_EQ(i,t->cell_value());
		t = t->left; 
	}
	t = grid.rows[7].right;
	for (int i =0; i < 6 ; i++){
		ASSERT_EQ(i+4,t->cell_value());
		t = t->right;
	}
	t = t->left;
	for (int i =6; i > 0 ; i--){
		ASSERT_EQ(i+3,t->cell_value());
		t = t->left; 
	}
	t = &(grid.grid[8][3]);
	for (int i = 0; i < 6 ; i++ ) {
		ASSERT_EQ(i+1,t->cell_value());
		t = t->right;
	}
	ASSERT_EQ(true,grid.regions[6].satisfy());
	ASSERT_EQ(true,grid.regions[7].satisfy());
	ASSERT_EQ(true,grid.regions[8].satisfy());
}
TEST(world_linking,world_linking_5){
	istringstream w("---147---\n---258---\n---369---\n---471---\n---582---\n---693---\n---714---\n---825---\n---936---\n");
	Sudoku_grid grid(w);
	Cell* t = grid.columns[3].down; 
	for (int i =0; i < 9 ; i++){
		ASSERT_EQ(i+1,t->cell_value());
		t = t->down; 
	}
	t = t->up;
	for (int i =9; i > 0 ; i--){
		ASSERT_EQ(i,t->cell_value());
		t = t->up; 
	}
	t = grid.columns[4].down;
	for (int i =0; i < 6 ; i++){
		ASSERT_EQ(i+4,t->cell_value());
		t = t->down;
	}
	t = t->up;
	for (int i =6; i > 0 ; i--){
		ASSERT_EQ(i+3,t->cell_value());
		t = t->up; 
	}
	t = &(grid.grid[3][5]);
	for (int i = 0; i < 6 ; i++ ) {
		ASSERT_EQ(i+1,t->cell_value());
		t = t->down;
	}
	ASSERT_EQ(true,grid.regions[1].satisfy());
	ASSERT_EQ(true,grid.regions[4].satisfy());
	ASSERT_EQ(true,grid.regions[7].satisfy());
}
TEST(world_linking,world_linking_6){
	istringstream w("------147\n------258\n------369\n------471\n------582\n------693\n------714\n------825\n------936\n");
	Sudoku_grid grid(w);
	Cell* t = grid.columns[6].down; 
	for (int i =0; i < 9 ; i++){
		ASSERT_EQ(i+1,t->cell_value());
		t = t->down; 
	}
	t = t->up;
	for (int i =9; i > 0 ; i--){
		ASSERT_EQ(i,t->cell_value());
		t = t->up; 
	}
	t = grid.columns[7].down;
	for (int i =0; i < 6 ; i++){
		ASSERT_EQ(i+4,t->cell_value());
		t = t->down;
	}
	t = t->up;
	for (int i =6; i > 0 ; i--){
		ASSERT_EQ(i+3,t->cell_value());
		t = t->up; 
	}
	t = &(grid.grid[3][8]);
	for (int i = 0; i < 6 ; i++ ) {
		ASSERT_EQ(i+1,t->cell_value());
		t = t->down;
	}
	ASSERT_EQ(true,grid.regions[2].satisfy());
	ASSERT_EQ(true,grid.regions[5].satisfy());
	ASSERT_EQ(true,grid.regions[8].satisfy());
	
}
/*
---------
---------
---------
123456789
456789123
789123456
---------
---------
---------	
*/
TEST(row_cover, row_cover_1) {
	istringstream w("---------\n---------\n---------\n123456789\n456789123\n789123456\n---------\n---------\n---------\n");
	Sudoku_grid grid(w);
	grid.cover_row_column(4,3);
	ASSERT_EQ(7,(grid.grid[3][0].cell_down())->cell_value());
	ASSERT_EQ(8,(grid.grid[3][1].cell_down())->cell_value());
	ASSERT_EQ(9,(grid.grid[3][2].cell_down())->cell_value());
	ASSERT_EQ(2,(grid.grid[3][4].cell_down())->cell_value());
	ASSERT_EQ(3,(grid.grid[3][5].cell_down())->cell_value());
	ASSERT_EQ(4,(grid.grid[3][6].cell_down())->cell_value());
	ASSERT_EQ(5,(grid.grid[3][7].cell_down())->cell_value());
	ASSERT_EQ(6,(grid.grid[3][8].cell_down())->cell_value());
	
	ASSERT_EQ(1,(grid.grid[5][0].cell_up())->cell_value());
	ASSERT_EQ(2,(grid.grid[5][1].cell_up())->cell_value());
	ASSERT_EQ(3,(grid.grid[5][2].cell_up())->cell_value());
	ASSERT_EQ(5,(grid.grid[5][4].cell_up())->cell_value());
	ASSERT_EQ(6,(grid.grid[5][5].cell_up())->cell_value());
	ASSERT_EQ(7,(grid.grid[5][6].cell_up())->cell_value());
	ASSERT_EQ(8,(grid.grid[5][7].cell_up())->cell_value());
	ASSERT_EQ(9,(grid.grid[5][8].cell_up())->cell_value());
	
}
TEST(row_cover, row_cover_2) {
	istringstream w("---------\n---------\n---------\n123456789\n456789123\n789123456\n---------\n---------\n---------\n");
	Sudoku_grid grid(w);
	grid.cover_row_column(3,3);
	ASSERT_EQ(0,(grid.grid[4][0].cell_up())->cell_value());
	ASSERT_EQ(0,(grid.grid[4][1].cell_up())->cell_value());
	ASSERT_EQ(0,(grid.grid[4][2].cell_up())->cell_value());
	ASSERT_EQ(0,(grid.grid[4][4].cell_up())->cell_value());
	ASSERT_EQ(0,(grid.grid[4][5].cell_up())->cell_value());
	ASSERT_EQ(0,(grid.grid[4][6].cell_up())->cell_value());
	ASSERT_EQ(0,(grid.grid[4][7].cell_up())->cell_value());
	ASSERT_EQ(0,(grid.grid[4][8].cell_up())->cell_value());
			
}
/*
------147
------258
------369
------471
------582
------693
------714
------825
------936
*/
TEST(column_cover, column_cover_1) {
	istringstream w("------147\n------258\n------369\n------471\n------582\n------693\n------714\n------825\n------936\n");
	Sudoku_grid grid(w);
	grid.cover_row_column(0,7);
	ASSERT_EQ(8,(grid.grid[1][6].cell_right())->cell_value());
	ASSERT_EQ(9,(grid.grid[2][6].cell_right())->cell_value());
	ASSERT_EQ(1,(grid.grid[3][6].cell_right())->cell_value());
	ASSERT_EQ(2,(grid.grid[4][6].cell_right())->cell_value());
	ASSERT_EQ(3,(grid.grid[5][6].cell_right())->cell_value());
	ASSERT_EQ(4,(grid.grid[6][6].cell_right())->cell_value());
	ASSERT_EQ(5,(grid.grid[7][6].cell_right())->cell_value());
	ASSERT_EQ(6,(grid.grid[8][6].cell_right())->cell_value());
	
	ASSERT_EQ(2,(grid.grid[1][8].cell_left())->cell_value());
	ASSERT_EQ(3,(grid.grid[2][8].cell_left())->cell_value());
	ASSERT_EQ(4,(grid.grid[3][8].cell_left())->cell_value());
	ASSERT_EQ(5,(grid.grid[4][8].cell_left())->cell_value());
	ASSERT_EQ(6,(grid.grid[5][8].cell_left())->cell_value());
	ASSERT_EQ(7,(grid.grid[6][8].cell_left())->cell_value());
	ASSERT_EQ(8,(grid.grid[7][8].cell_left())->cell_value());
	ASSERT_EQ(9,(grid.grid[8][8].cell_left())->cell_value());
}
TEST(column_cover,column_cover_2) {
	istringstream w("------147\n------258\n------369\n------471\n------582\n------693\n------714\n------825\n------936\n");
	Sudoku_grid grid(w);
	grid.cover_row_column(0,6);
	ASSERT_EQ(0	,(grid.grid[1][7].cell_left())->cell_value());
	ASSERT_EQ(0	,(grid.grid[2][7].cell_left())->cell_value());
	ASSERT_EQ(0	,(grid.grid[3][7].cell_left())->cell_value());
	ASSERT_EQ(0	,(grid.grid[4][7].cell_left())->cell_value());
	ASSERT_EQ(0	,(grid.grid[5][7].cell_left())->cell_value());
	ASSERT_EQ(0	,(grid.grid[6][7].cell_left())->cell_value());
	ASSERT_EQ(0	,(grid.grid[7][7].cell_left())->cell_value());
	ASSERT_EQ(0	,(grid.grid[8][7].cell_left())->cell_value());
	
}