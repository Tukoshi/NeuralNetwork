#include "NeuralNet.h"

NeuralNet::NeuralNet(vector <int> topology)
{
	this->topology = topology;
	this->topologySize = topology.size();
	for (int i = 0; i < this->topologySize; i++)
	{
		Layer * L = new Layer(topology.at(i));
		this->layers.push_back(L);
	}

	for (int i = 0; i < this->topologySize - 1; i++)
	{
		Matrix * M = new Matrix(topology.at(i), topology.at(i + 1), true);
		this->weights.push_back(M);
	}
}
NeuralNet::~NeuralNet()
{
	for (int i = 0; i < this->topologySize; i++)
	{
		delete this->layers.at(i);
	}

	for (int i = 0; i < this->topologySize - 1; i++)
	{
		delete this->weights.at(i);
	}
}
void NeuralNet::setCurrentInput(vector<double> input)
{
	this->input = input;
	int size = input.size();
	for (int i = 0; i < size; i++)
	{
		this->layers.at(0)->setval(i, input.at(i));
	}

}
void NeuralNet::setHiddenLayer(vector<double> input, int index)
{
	int size = this->layers.at(index)->getsize();
	
	for (int i = 0; i < size; i++)
	{
		this->layers.at(index)->setval(i, input.at(i));
	}
}
void NeuralNet::printCurrentInput()
{
	layers.at(0)->print_layer(0);
}

void NeuralNet::printWeights(int index = 0)
{
	cout << "-------------------\n";
	cout << "Weights between Layers #"<< index+1 <<" and #"<< index + 2<<"\n";
	this->weights.at(index)->consolePrint();
	cout << "-------------------\n";
}


void NeuralNet::printNet(int type = 0)
{
	cout << "-------------------\n";
	int size = this->layers.size();
	switch (type)
	{
	case 0:
		cout << "DALIVERED VALUES\n";
		break;
	case 1:
		cout << "ACTIVATION VALUES\n";
			break;
	case 2:
		cout << "DERIVATIVE VALUES\n";
			break;
	default:
		
		break;
	}
	for (int i = 0; i < size; i++)
	{
		cout << "Layer #" << i + 1 << endl;
		this->layers.at(i)->print_layer(type);
	}
	cout << "-------------------\n";
}

Matrix * NeuralNet::getNeuronMatrix(int index)
{
	return this->layers.at(index)->matrixifyValues();
}
Matrix * NeuralNet::getNeuronActMatrix(int index)
{
	return this->layers.at(index)->matrixifyActValues();
}
Matrix * NeuralNet::getNeuronDerMatrix(int index)
{
	return this->layers.at(index)->matrixifyDerValues();
}
Matrix * NeuralNet::getWeightMatrix(int index)
{
	return this->weights.at(index);
}


void NeuralNet::feedforward(int function)
{
	int size = this->layers.size() - 1;

	for (int i = 0; i < size; i++)
	{
		Matrix * a = this->getNeuronMatrix(i);

		if (i != 0)
		{
			a = this->getNeuronActMatrix(i);
		}
		Matrix *b = this->getWeightMatrix(i);
		Matrix *c = a->multiplybymatrix(*b);;
		int c_size = c->getNumRows();

		for (int c_index = 0; c_index < c_size; c_index++)
		{
			this->setNeuronValue(i+1, c_index, c->get_value(c_index, 0), function);
		}
		delete a, b, c;
	}
}

void NeuralNet::setNeuronValue(int layerIndex, int neuronIndex, double value, int function)
{
	
	this->layers.at(layerIndex)->setval(neuronIndex, value, function);
}