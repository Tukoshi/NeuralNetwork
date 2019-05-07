#include "Layer.h"


Layer::Layer(int size)
{
	this->size = size;
	for (int i = 0; i < size; i++)
	{
		Neuron * n = new Neuron(0.00);
		neurons.push_back(n);
	}
}
Layer::~Layer()
{
	
	for (int i = 0; i < this->size; i++)
	{
		delete this->neurons.at(i);
	}
}

// get matrixified delivered values
Matrix * Layer::matrixifyValues()
{
	
	Matrix * m = new Matrix(1, this->size, true);
	for (int i = 0; i < this->size; i++)
	{
		m->set_value(0, i, this->neurons.at(i)->get_value());
	}
	return m;

}

// get matrixified activation values
Matrix * Layer::matrixifyActValues()
{
	Matrix * m = new Matrix(1, this->size, true);
	for (int i = 0; i < this->size; i++)
	{
		m->set_value(0, i, this->neurons.at(i)->get_avalue());
	}
	return m;
}
// get matrixified derivative values
Matrix * Layer::matrixifyDerValues()
{
	Matrix * m = new Matrix(1, this->size, true);
	for (int i = 0; i < this->size; i++)
	{
		m->set_value(0, i, this->neurons.at(i)->get_dvalue());
	}
	return m;
}

void Layer::print_layer(int which = 0)
{
	int size = this->neurons.size();
	for (int i = 0; i < size; i++)
	{
		if (which == 0) cout << this->neurons.at(i)->get_value() << " ";
		else if (which == 1) cout << this->neurons.at(i)->get_avalue() << " ";
		else if (which == 2) cout << this->neurons.at(i)->get_dvalue() << " ";
	}
	cout << "\n";
}