#include "NeuralNet.h"
NeuralNet::NeuralNet(vector <int> topology)
{
	this->topology = topology;
	this->topologySize = topology.size();
	this->chosen_act_func = 1;
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
NeuralNet::NeuralNet(vector <int> topology, int function)
{
	this->topology = topology;
	this->topologySize = topology.size();
	this->chosen_act_func = function;
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
	for (int i = 0; i < this->topologySize - 1; i++)
	{
		delete this->GradientMatrices.at(i);
	}
}
void NeuralNet::setCurrentInput(vector<double> input)
{
	this->input = input;
	int size = input.size();
	for (int i = 0; i < size; i++)
	{
		this->layers.at(0)->setNeuron(i, input.at(i));
	}
}
void NeuralNet::printCurrentInput()
{
	cout << "Delivered:\t";
	layers.at(0)->print(0);
	cout << "Activated:\t";
	layers.at(0)->print(1);
	cout << "Derive:   \t";
	layers.at(0)->print(2);
}
void NeuralNet::printWeights(int index = 0)
{
	cout << "-------------------\n";
	cout << "Weights between Layers #" << index + 1 << " and #" << index + 2 << "\n";
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
		this->layers.at(i)->print(type);
		cout<< endl;
	}
	cout << "-------------------\n";
}
void NeuralNet::printLayer(int index, int type)
{
	this->layers.at(index)->print(type);
}
Matrix * NeuralNet::getNeuronMatrix(int index)
{
	return this->layers.at(index)->matrixifyDelivered();
}
Matrix * NeuralNet::getNeuronActMatrix(int index)
{
	return this->layers.at(index)->matrixifyActivated();
}
Matrix * NeuralNet::getNeuronDerMatrix(int index)
{
	return this->layers.at(index)->matrixifyDerived();
}
Matrix * NeuralNet::getWeightMatrix(int index)
{
	return this->weights.at(index);
}
void NeuralNet::setNeuronValue(int layerIndex, int neuronIndex, double value, int function)
{
	this->layers.at(layerIndex)->setNeuron(neuronIndex, value, function);
}
void NeuralNet::setNeuronValue(int layerIndex, int neuronIndex, double value)
{
	this->layers.at(layerIndex)->setNeuron(neuronIndex, value, this->chosen_act_func);
}
void NeuralNet::feedforward(int function)
{
	int size = this->layers.size() - 1;
	this->chosen_act_func = function;
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
			this->setNeuronValue(i + 1, c_index, c->get_value(c_index, 0), this->chosen_act_func);
		}
		delete a, b, c;
	}
}
void NeuralNet::feedforward()
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
			this->setNeuronValue(i + 1, c_index, c->get_value(c_index, 0), this->chosen_act_func);
		}
		delete a, b, c;
	}
}

void NeuralNet::setTarget(vector<double> target)
{
	this->target = target;
}
void NeuralNet::calculate_error()
{
	this->errors.clear();
	this->error = 0.0;
	int size = this->layers.at(this->topologySize - 1)->getSize();
	Matrix * new_m = this->layers.at(this->topologySize - 1)->matrixifyActivated();

	for (int i = 0; i < size; i++)
	{
		double tempErr = abs(new_m->get_value(0, i) - this->target.at(i));
		this->errors.push_back(tempErr);
		this->error += tempErr;
	}
}

void NeuralNet::printError()
{
	cout << "Total Error: " << this->error << endl;
	int size = this->errors.size();
	for (int i = 0; i < size; i++)
	{
		cout << this->errors.at(i) << " ";
	}
	cout << endl;
}
void  NeuralNet::backpropagation(double speed = 0.00001)
{
	this->calculate_error();
	vector <Matrix *> newWeights;
	Matrix * gradients;

	int OutLayerIndex = this->topologySize - 1;
	Matrix * derivedvals = this->layers.at(OutLayerIndex)->matrixifyDerived();
	Matrix * gradientYtoZ = new Matrix(1, this->layers.at(OutLayerIndex)->getSize(), false);
	{
		int size = this->errors.size();
		for (int i = 0; i < size; i++)
		{
			gradientYtoZ->set_value(0, i, derivedvals->get_value(0, i) * errors.at(i));
		}
	}
	int lastHiddenLayerIndex = OutLayerIndex - 1;
	Layer * LastHiddenLayer = this->layers.at(lastHiddenLayerIndex);
	Matrix * WeightsOutToHidden = this->weights.at(OutLayerIndex - 1);
	gradientYtoZ->transpose();
	Matrix * LastHiddenActivatedVals = LastHiddenLayer->matrixifyActivated();
	Matrix * deltaOutToHidden = gradientYtoZ->multiplybymatrix(*LastHiddenActivatedVals);
	gradientYtoZ->transpose();
	Matrix * newWeightsOutToHiden = new Matrix(deltaOutToHidden->getNumRows(),
		deltaOutToHidden->getNumCols(), 0.0);

	for (int row = 0; row < deltaOutToHidden->getNumRows(); row++)
	{
		for (int col = 0; col < deltaOutToHidden->getNumCols(); col++)
		{
			double originalWeight = WeightsOutToHidden->get_value(row, col);
			double deltaWeight = speed * deltaOutToHidden->get_value(row, col);
			newWeightsOutToHiden->set_value(row, col, originalWeight - deltaWeight);
		}
	}

	newWeights.push_back(newWeightsOutToHiden);

	gradients = new Matrix(gradientYtoZ->getNumRows(), gradientYtoZ->getNumCols(), 0.0);

	for (int row = 0; row < gradients->getNumRows(); row++)
	{
		for (int col = 0; col < gradients->getNumCols(); col++)
		{
			gradients->set_value(row, col, gradientYtoZ->get_value(row, col));
		}
	}
	delete gradientYtoZ, newWeightsOutToHiden, deltaOutToHidden, LastHiddenActivatedVals;

	for (int i = (OutLayerIndex - 1); i > 0; i--)
	{
		Layer *l = this->layers.at(i);
		Matrix * derivedHidden = l->matrixifyDerived();
		Matrix * ActivatedHidden = l->matrixifyActivated();
		Matrix * derivedGradient = new Matrix(1, l->getSize(), 0.0);
		Matrix * weightMatrix = this->weights.at(i);
		Matrix * originalWeights = this->weights.at(i - 1);

		{
			int sizey = weightMatrix->getNumRows();
			int sizex = weightMatrix->getNumCols();

			for (int r = 0; r < sizey; r++)
			{
				double sum = 0.0;
				for (int c = 0; c < sizex; c++)
				{
					sum += gradients->get_value(0, c) * weightMatrix->get_value(r, c);
				}
				double g = sum * ActivatedHidden->get_value(0, r);
				derivedGradient->set_value(0, r, g);
			}

		}
		Matrix * leftNeurons;
		if ((i - 1) != 0)
		{
			leftNeurons = this->layers.at(i - 1)->matrixifyActivated();
		}
		else
		{
			leftNeurons = this->layers.at(i - 1)->matrixifyDelivered();
		}

		derivedGradient->transpose();
		Matrix * deltaWeights = derivedGradient->multiplybymatrix(*leftNeurons);
		Matrix * newWeightsHidden = new Matrix(deltaWeights->getNumRows(),
			deltaWeights->getNumRows(),
			0.0);
		{
			int sizey = deltaWeights->getNumRows();
			int sizex = deltaWeights->getNumCols();
			for (int r = 0; r < sizey; r++)
			{
				for (int c = 0; c < sizex; c++)
				{
					double w = originalWeights->get_value(r, c);
					double d = speed * deltaWeights->get_value(r, c);
					newWeightsHidden->set_value(r, c, w - d);
				}
			}
		}
		{
			newWeights.push_back(newWeightsHidden);
			delete gradients;
			gradients = new Matrix(derivedGradient->getNumRows(),
				derivedGradient->getNumCols(),
				0.0);
			int sizey = gradients->getNumRows();
			int sizex = gradients->getNumCols();
			for (int r = 0; r < sizey; r++)
			{
				for (int c = 0; c < sizex; c++)
				{
					gradients->set_value(r, c, derivedGradient->get_value(r, c));
				}
			}

		}
		delete derivedGradient, leftNeurons, deltaWeights, derivedHidden;
	}
	int size = this->weights.size();
	for (int i = 0; i < size; i++)
	{
		delete this->weights.at(i);
	}
	this->weights.clear();
	for (int i = newWeights.size() - 1; i >= 0; i--)
	{
		this->weights.push_back(newWeights.at(i));
	}

}
