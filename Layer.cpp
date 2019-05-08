#include "Layer.h"


void Layer::activateLayer()
{
	for (int i = 0; i < this->size; i++)
	{
		this->neurons.at(i)->activate();
	}
}
void Layer::activateLayer(int function)
{
	for (int i = 0; i < this->size; i++)
	{
		this->neurons.at(i)->activate(function);
	}
}
void Layer::activateLayer(int function, double a)
{
	for (int i = 0; i < this->size; i++)
	{
		this->neurons.at(i)->activate(function, a);
	}
}


void Layer::erase()
{
	for (int i = 0; i < this->size; i++)
	{
		delete this->neurons.at(i);
	}
	this->neurons.clear();
	this->size = 0;

}

void Layer::setLayer(vector <double> values)
{
	this->erase();
	this->size = size;
	for (int i = 0; i < this->size; i++)
	{
		Neuron * new_neuron = new Neuron(values.at(i));
		this->neurons.push_back(new_neuron);
	}
}

void Layer::setNeuron(int index, double value)
{
	this->neurons.at(index)->setvalue(value);
}
void Layer::setNeuron(int index, double value, int function)
{
	this->neurons.at(index)->setvalue(value, function);
}
void Layer::setNeuron(int index, double value, int function, double a)
{
	this->neurons.at(index)->setvalue(value, function, a);
}

void Layer::print(int type)
{
	for (int i = 0; i < this->size; i++)
	{
		if (type == 0)
		{
			cout << this->neurons.at(i)->get_value() << "\n";
		}
		else if (type == 1)
		{
			cout << this->neurons.at(i)->get_avalue() << "\n";
		}
		else if (type == 2)
		{
			cout << this->neurons.at(i)->get_dvalue() << "\n";
		}
	}
}


Layer::Layer(int size)
{
	this->size = size;
	for (int i = 0; i < this->size; i++)
	{
		Neuron * new_neuron = new Neuron();
		this->neurons.push_back(new_neuron);
	}
	this->activateLayer();
}
Layer::Layer(vector <double> values)
{
	this->size = values.size();
	for (int i = 0; i < this->size; i++)
	{
		Neuron * new_neuron = new Neuron(values.at(i));
		this->neurons.push_back(new_neuron);
	}
	this->activateLayer();
}
Layer::Layer(vector <double> values, int function)
{
	this->size = values.size();
	for (int i = 0; i < this->size; i++)
	{
		Neuron * new_neuron = new Neuron(values.at(i), function);
		this->neurons.push_back(new_neuron);
	}
	this->activateLayer();
}
Layer::Layer(vector <double> values, int function, double a)
{
	this->size = values.size();
	for (int i = 0; i < this->size; i++)
	{
		Neuron * new_neuron = new Neuron(values.at(i), function);
		this->neurons.push_back(new_neuron);
	}
	this->activateLayer();
}
Layer::~Layer()
{
	for (int i = 0; i < this->size; i++)
	{
		delete this->neurons.at(i);
	}
}


Matrix * Layer::matrixifyDelivered()
{
	Matrix * new_m = new Matrix(this->size, 1, true);
	for (int i = 0; i < this->size; i++)
	{
		new_m->set_value(i, 1, this->neurons.at(i)->get_value());
	}
	return new_m;
}
Matrix * Layer::matrixifyActivated()
{
	Matrix * new_m = new Matrix(this->size, 1, true);
	for (int i = 0; i < this->size; i++)
	{
		new_m->set_value(i, 1, this->neurons.at(i)->get_avalue());
	}
	return new_m;
}
Matrix * Layer::matrixifyDerived()
{
	Matrix * new_m = new Matrix(this->size, 1, true);
	for (int i = 0; i < this->size; i++)
	{
		new_m->set_value(i, 1, this->neurons.at(i)->get_dvalue());
	}
	return new_m;
}
