#pragma once

#include "Matrix.h"
#include "Neuron.h"
#include <vector>

using std::cout;
using std::endl;

class Layer
{
public:

	Layer(int size);
	Layer(vector <double> values);
	Layer(vector <double> values, int function);
	Layer(vector <double> values, int function, double a);

	~Layer();

	void print(int);

	void setNeuron(int index, double value);
	void setNeuron(int index, double value, int function);
	void setNeuron(int index, double value, int function, double a);

	void setLayer(vector <double> values);

	Matrix * matrixifyDelivered();
	Matrix * matrixifyActivated();
	Matrix * matrixifyDerived();

	void activateLayer();
	void activateLayer(int function);
	void activateLayer(int function, double a);

	void erase();

private:
	int size;
	vector <Neuron *> neurons;
};
