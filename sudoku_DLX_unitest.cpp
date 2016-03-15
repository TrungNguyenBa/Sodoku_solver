#include <iostream> 
#include <sstream>  
#include <string>	
#include <utility>	

#include "gtest/gtest.h"
#define private public
#define protected public
#include "sudoku_DLX.h"
#define private private
#define protected protected
using namespace std;
TEST(Initilize, test_1) {
	EXC grid;
	grid.initilize(0,0,8);
	ASSERT_EQ(1,grid.grid[7][0].cell_value());
	ASSERT_EQ(1,grid.grid[7][88].cell_value());
	ASSERT_EQ(1,grid.grid[7][169].cell_value());
	ASSERT_EQ(1,grid.grid[7][250].cell_value());
}
TEST(Initilize, test_2) {
	EXC grid;	
	grid.initilize(0,0,0);
	for (int i = 0; i < 9; i++){
		ASSERT_EQ(1,grid.grid[i][0].cell_value());
		ASSERT_EQ(1,grid.grid[i][81+i].cell_value());
		ASSERT_EQ(1,grid.grid[i][162+i].cell_value());
		ASSERT_EQ(1,grid.grid[i][243+i].cell_value());
	}
}
TEST(Initilize, test_3) {
	EXC grid;
	grid.initilize(0,3,4);
	ASSERT_EQ(1,grid.grid[30][3].cell_value());
	ASSERT_EQ(1,grid.grid[30][84].cell_value());
	ASSERT_EQ(1,grid.grid[30][192].cell_value());
	ASSERT_EQ(1,grid.grid[30][255].cell_value());
}
TEST(Initilize, test_4) {
	EXC grid;
	grid.initilize(3,3,0);
	for (int i = 0; i < 9; i++){
		ASSERT_EQ(1,grid.grid[270+i][30].cell_value());
		ASSERT_EQ(1,grid.grid[270+i][108+i].cell_value());
		ASSERT_EQ(1,grid.grid[270+i][189+i].cell_value());
		ASSERT_EQ(1,grid.grid[270+i][279+i].cell_value());
	}
}
TEST(Initilize, test_5) {
	EXC grid;
}
TEST(Initilize, test_6) {
	EXC grid;
}
TEST(Initilize, test_7) {
	EXC grid;
}
TEST(Initilize, test_8) {
	EXC grid;
}
TEST(LINKING, row_linking_t) {
	EXC grid;
	grid.initilize(0,0,8);
	grid.linking();
	Cell* t = &(grid.nc);
	Cell::go_right(t);
	Cell::go_down(t);
	ASSERT_EQ(&(grid.grid[7][0]),t);
	Cell::go_right(t);
	ASSERT_EQ(&(grid.grid[7][88]),t);
	Cell::go_right(t);
	ASSERT_EQ(&(grid.grid[7][169]),t);
	Cell::go_right(t);
	ASSERT_EQ(&(grid.grid[7][250]),t);
	
}
TEST(LINKING, row_linking_t_2) {
	EXC grid;
	grid.initilize(0,0,0);
	grid.linking();
	Cell * t = &(grid.nc);
	Cell::go_right(t);
	Cell::go_down(t);
	for (int i =0; i < 9; ++i) {
		ASSERT_EQ(&(grid.grid[i][0]),t);
		int k =1;
		Cell* te = t;
		Cell::go_right(te);
		for (; te != t; Cell::go_right(te)) {
			ASSERT_EQ(&(grid.grid[i][81*k +i]),te);
			++k;
		}
		Cell::go_down(t);
	}
	//Cell::go_down(t);
	ASSERT_EQ(&(grid.hc[0]),t);

}
TEST(LINKING, row_linking_1){
	istringstream w("---------\n---------\n---------\n---------\n---------\n---------\n---------\n---------\n---------\n");
	EXC grid(w);
}
TEST(LINKING, row_linking_2) {

}

TEST(LINKING, column_linking_1) {
	istringstream w("---------\n---------\n---------\n---------\n---------\n---------\n---------\n---------\n---------\n");
	EXC grid(w);
}
TEST(LINKING, column_linking_2) {

}

TEST(LINKING, world_linking_1) {
	istringstream w("---------\n---------\n---------\n---------\n---------\n---------\n---------\n---------\n---------\n");
	EXC grid(w);
}
TEST(LINKING, world_linking_2) {

}

//cover TEST
TEST(COVERING, cover_1) {

}
TEST(COVERING, cover_2) {

}
TEST(COVERING, cover_3) {

}
TEST(COVERING, cover_4) {
	
}