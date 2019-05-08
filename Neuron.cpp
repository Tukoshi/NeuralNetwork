#include "Neuron.h"

void Neuron::print()
{
	cout << "Delivered: " << this->delVal << " \tActivated:  " << this->actVal << "\t Derivative:  " << this->derVal << "\n";
}
Neuron::Neuron()
{
	Activators activator;
	this->delVal = 0.0;
	this->actVal = activator.activate(1, this->delVal);
	this->derVal = activator.derive(1, this->delVal);
}
Neuron::Neuron(double x)
{
	Activators activator;
	this->delVal = x;
	this->actVal = activator.activate(1, this->delVal);
	this->derVal = activator.derive(1, this->delVal);
}

Neuron::Neuron(double x, int function)
{
	Activators activator;
	this->delVal = x;
	this->actVal = activator.activate(function, this->delVal);
	this->derVal = activator.derive(function, this->delVal);
}
Neuron::Neuron(double x, int function, double a)
{
	Activators activator(a);
	this->delVal = x;
	this->actVal = activator.activate(function, this->delVal);
	this->derVal = activator.derive(function, this->delVal);
}

void Neuron::activate()
{
	Activators activator;
	this->actVal = activator.activate(1, this->delVal);
	this->derVal = activator.derive(1, this->delVal);
}
void Neuron::activate(int function)
{
	Activators activator;
	this->actVal = activator.activate(function, this->delVal);
	this->derVal = activator.derive(function, this->delVal);
}
void Neuron::activate(int function, double a)
{
	Activators activator(a);
	this->actVal = activator.activate(function, this->delVal);
	this->derVal = activator.derive(function, this->delVal);
}

void Neuron::setvalue(double value)
{
	this->delVal = value;
	this->activate();
}
void Neuron::setvalue(double value, int function)
{
	this->delVal = value;
	this->activate(function);
}
void Neuron::setvalue(double value, int function, double a)
{
	this->delVal = value;
	this->activate(function, a);
}

