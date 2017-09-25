#ifndef SUDOKU
#define SUDOKU

#include <string>
#include <vector>

class Cell;
class Solver {
public:
	Solver(int matrix[][9]); // takes a 9x9 array of int
	~Solver();
	bool solve(); // solve and store the full solution to grid, return TRUE. If unsolvable: return FALSE
	std::string* getResult(); // returns the results in form of a 9-element string array
	void printGrid();
private:
	Cell* grid[9][9];
	int checkCount;
	std::string result[9];
	void addNeighbors();
	std::vector <Cell*> unk; // stores all unknowns at the beginning of puzzle.
};

class Cell {
public:	
	int val;
	bool check(); // returns true if there is no conflict with neighbors
	Cell (int);
	Cell* neighbor[20];
};

#endif