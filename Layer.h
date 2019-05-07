#pragma once
#include "Matrix.h"
#include "Neuron.h"
#include <vector>
#include <iostream>
using namespace std;

class Layer
{
public:
	// size means how many neurons should be in this layer
	Layer(int size);
	~Layer();
	// set specifis value
	void setval(int index, double value)
	{
		neurons[index]->set_val(value); 
	}
	void setval(int index, double value, int function)
	{
		neurons[index]->set_val(value, function);
	}
	// get delivered, activation or derivative value as matrix 1 x size
	Matrix * matrixifyValues();
	Matrix * matrixifyActValues();
	Matrix * matrixifyDerValues();
	// print whole layer
	void print_layer(int which);
	int getsize() { return this->size; }
private:
	int size;
	vector<Neuron *> neurons;
};