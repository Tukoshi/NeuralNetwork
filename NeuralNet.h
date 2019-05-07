#pragma once
#include <vector>
#include "Layer.h"
#include "Neuron.h"
#include "Matrix.h"

class NeuralNet
{
public:
	NeuralNet(vector <int> topology);
	~NeuralNet();
	void setCurrentInput(vector<double> input);
	void printCurrentInput();
	void feedforward(int function_forward);
	Matrix * getNeuronMatrix(int index);
	Matrix * getNeuronActMatrix(int index);
	Matrix * getNeuronDerMatrix(int index);
	Matrix * getWeightMatrix(int index);
	void setHiddenLayer(vector<double> input, int index);
	void setNeuronValue(int layerIndex, int neuronIndex, double value, int function);
	int topologySize;
	void printWeights(int index);
	vector <int>	  topology;
	vector <Layer * > layers;
	vector <Matrix *> weights;
	vector <double>	  input;
	void printNet(int type);

private:

};