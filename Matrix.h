#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Matrix
{
public:
	// constructor
	Matrix(int rows, int cols, bool israndom);
	Matrix(int rows, int cols, double fillwith);
	// matrix functions
	Matrix * transpose();
	void consolePrint();
	Matrix * multiplybymatrix(Matrix M);
	// help functions
	double getRandomNumber() { return (double)rand() / (double)RAND_MAX; }
	// matrix propperties
	void   set_value(int r, int c, double v) { this->values.at(r).at(c) = v; }
	double get_value(int r, int c) { return this->values.at(r).at(c); }
	int getNumCols();
	int getNumRows();
private:
	double mul_col_with_row(int row, Matrix M, int column);
	int nrows, ncols;
	vector < vector<double> > values;
};


