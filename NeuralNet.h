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

	void printCurrentInput();
	void printWeights(int index);
	void printNet(int type);
	void printLayer(int index, int type);
	void printError();

	Matrix * getNeuronMatrix(int index);
	Matrix * getNeuronActMatrix(int index);
	Matrix * getNeuronDerMatrix(int index);
	Matrix * getWeightMatrix(int index);

	void setNeuronValue(int layerIndex, int neuronIndex, double value, int function);
	void setNeuronValue(int layerIndex, int neuronIndex, double value);
	void setCurrentInput(vector<double> input);


	void feedforward(int function_forward);
	void feedforward();

	void setTarget(vector<double> target);
	void calculate_error();
	
	void backpropagation(double speed);
	vector <Matrix *> GradientMatrices;
	double error;

private:
	int chosen_act_func;
	vector <double> errors;
	vector <double> target;
	vector <double> historicalError;

	int topologySize;
	vector <int>	  topology;
	vector <Layer * > layers;
	vector <Matrix *> weights;
	vector <double>	  input;
};