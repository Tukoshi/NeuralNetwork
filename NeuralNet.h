#pragma once
#include <vector>
#include "Layer.h"
#include "Neuron.h"
#include "Matrix.h"

class NeuralNet
{
public:
	NeuralNet(vector <int> topology);
	NeuralNet::NeuralNet(vector <int> topology, int function);
	~NeuralNet();

	void setCurrentInput(vector<double> input);
	void printCurrentInput();

	void printWeights(int index);
	void printNet(int type);
	void printLayer(int index, int type);

	Matrix * getNeuronMatrix(int index);
	Matrix * getNeuronActMatrix(int index);
	Matrix * getNeuronDerMatrix(int index);
	Matrix * getWeightMatrix(int index);

	void setNeuronValue(int layerIndex, int neuronIndex, double value, int function);
	void setNeuronValue(int layerIndex, int neuronIndex, double value);

	void feedforward(int function_forward);
	void feedforward();

private:
	int chosen_act_func;
	int topologySize;
	vector <int>	  topology;
	vector <Layer * > layers;
	vector <Matrix *> weights;
	vector <double>	  input;
};