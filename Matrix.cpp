#include "Matrix.h"

double Matrix::mul_col_with_row(int row, Matrix M, int column)
{
	/*
		dot product of row number (INT row argument) AND (column number  INT column of MATRIX M)
	*/
	double sum = 0.0;

	for (int i = 0; i < this->ncols; i++)
	{
		sum += this->values[row][i] * M.values[i][column];
	}
	return sum;
}

Matrix * Matrix::multiplybymatrix(Matrix M)
{
	/*
		Multiplication of two matrices, this and given in argument as
		THIS times GIVEN.
		if you want GIVEN times THIS use this method but in Matrix M while
		THIS matrix should be the one that is given as argument.
												 [3]
		[1,1,1]	      [1,1,1,1,1]    [3]
		[1,1,1] times [1,1,1,1,1] is [3] etc.
		[1,1,1]	      [1,1,1,1,1]    [3]
							 [3]

		Works fine if real matrix multiplicaiton(shapes) rules are obeyed
		If they're not obeyed method returns zero filled matrix
	*/
	Matrix * new_m = new Matrix(M.ncols, this->nrows, false);

	if (this->ncols == M.nrows)
	{
		for (int row = 0; row < M.ncols; row++)
		{
			for (int col = 0; col < this->nrows; col++)
			{
				double sum_of_mul = this->mul_col_with_row(col, M, row);
				new_m->values[row][col] = sum_of_mul;
			}
		}
		return new_m;
	}
	else
	{
		return NULL;
	}

}

Matrix * Matrix::transpose()
{
	Matrix * new_m = new Matrix(this->ncols, this->nrows, false);
	for (int i = 0; i < this->nrows; i++)
	{
		for (int e = 0; e < this->ncols; e++)
		{
			new_m->set_value(e, i, this->values[i][e]);
		}
	}
	return new_m;
}

Matrix::Matrix(int rows, int cols, bool israndom)
{
	this->nrows = rows;
	this->ncols = cols;
	for (int i = 0; i < nrows; i++)
	{
		vector <double> colValues;
		for (int e = 0; e < ncols; e++)
		{
			double r = 0.0;
			if (israndom) r = getRandomNumber();
			colValues.push_back(r);
		}
		values.push_back(colValues);
	}
}
Matrix::Matrix(int rows, int cols, double fillwith)
{
	this->nrows = rows;
	this->ncols = cols;
	for (int i = 0; i < nrows; i++)
	{
		vector <double> colValues;
		for (int e = 0; e < ncols; e++)
		{
			colValues.push_back(fillwith);
		}
		values.push_back(colValues);
	}
}

void Matrix::consolePrint()
{
	if (this->nrows == 0 || this->ncols && 0) cout << "\nempty\n";
	else
	{
		for (int i = 0; i < this->nrows; i++)
		{
			for (int e = 0; e < this->ncols; e++)
			{
				cout << values.at(i).at(e) << " ";
			}
			cout << "\n";
		}
	}
}
int Matrix::getNumCols()
{
	return this->ncols;
}

int Matrix::getNumRows()
{
	return this->nrows;
}
