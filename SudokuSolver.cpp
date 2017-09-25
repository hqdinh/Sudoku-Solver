#include "SudokuSolver.h"
#include <iostream>
#include <Windows.h>

Solver::Solver(int matrix[][9])
{
	unk.clear();
	checkCount = 0;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			grid[i][j] = new Cell(matrix[i][j]); // add cell to grid
			if (matrix[i][j] == 0)
				unk.push_back(grid[i][j]);
		}
	addNeighbors();
}

std::string* Solver::getResult() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			result[i] += (grid[i][j]->val + '0');
	return result;
}

bool Solver::solve() {
	if (unk.empty()) return true; //no unknowns in puzzle
	std::vector<Cell*>::iterator it = unk.begin();
	while (it != unk.end()) {
		while (!(*it)->check()) {
			(*it)->val++;
		}
		
		if ((*it)->val >= 10) {
			(*it)->val = 0;
			if (it == unk.begin())
				return false;
			(*--it)->val++;
		} else it++;
	}
	return true;
}

void Solver::printGrid() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (grid[i][j]->val == 0 || grid[i][j]->val == 10)
				std::cout << ' ';
			else
				std::cout << grid[i][j]->val;
			if (j % 3 == 2)
				std::cout << ' ';
		}
		std::cout << std::endl;
		if (i % 3 == 2)
			std::cout << std::endl;
	}
}



void Solver::addNeighbors() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			for (int k = 0; k < 8; k++) {
				grid[i][j]->neighbor[k] = grid[i][(j + k + 1) % 9]; // neighbors in the same row
				grid[i][j]->neighbor[k + 8] = grid[(i + k + 1) % 9][j]; // neighbors in the same column
			}
			// 4 remaining neighbors in the 3x3 box
			int x1, x2, y1, y2;
			x1 = i + 1 - 3 * ((i + 1) / 3 - (i / 3));
			x2 = i + 2 - 3 * ((i + 2) / 3 - (i / 3));
			y1 = j + 1 - 3 * ((j + 1) / 3 - (j / 3));
			y2 = j + 2 - 3 * ((j + 2) / 3 - (j / 3));
			grid[i][j]->neighbor[16] = grid[x1][y1];
			grid[i][j]->neighbor[17] = grid[x1][y2];
			grid[i][j]->neighbor[18] = grid[x2][y1];
			grid[i][j]->neighbor[19] = grid[x2][y2];
		}
}

Solver::~Solver(){
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			delete grid[i][j];		
}

Cell::Cell(int value) : val(value) { }

bool Cell::check() {
	if (val == 0) return false; // CAREFUL!!
	for (int i = 0; i < 20; i++)
		if (val == neighbor[i]->val)
			return false;
	return true;
}