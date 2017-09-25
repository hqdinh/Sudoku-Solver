#include <iostream>
#include <string>
#include <fstream>
#include "SudokuSolver.h"
#include <ctime>

using namespace std;

int main()
{
	// get in put puzzle from input.txt to intMatrix
	string initialData[9] = {};
	ifstream infile("input.txt");
	if (!infile.is_open())
		return -1;
	if (infile.is_open())
		for (int i = 0; i < 9; ++i)
			infile >> initialData[i];
	infile.close();

	int intMatrix[9][9];
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			intMatrix[i][j] = initialData[i][j] - '0';

	// solve the puzzle with object 'puzzle'
	int start_s = clock();
	Solver puzzle(intMatrix);
	bool solved = puzzle.solve();
	int stop_s = clock();
	cout << "Solving time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 <<  " ms" << endl;
	
	if (!solved) return -1;

	// print results
	string *res = puzzle.getResult();
	for (int i = 0; i < 9; i++)	{
		for (int j = 0; j < 9; j++)	{
			if (res[i][j] == '0')
				cout << ' ';
			else 
				cout << res[i][j];
			if (j % 3 == 2)
				cout << ' ';
		}
		cout << endl;
		if (i % 3 == 2)
			cout << endl;
	}

	// write results to output.txt
	ofstream outfile("output.txt");
	for (int i = 0; i < 9; i++) 
		outfile << res[i] << endl;
	outfile.close();

	return 0;
}

