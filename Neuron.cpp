#include "Neuron.h"

Neuron::Neuron()
{
	// both bias and delivered values seto to 0 and 
	// calculate default activation function sigmoid and its derivatove
	this->bias = this->delVal = 0.0;
	this->activate(0);
	this->derive(0);
}

Neuron::Neuron(double x, double bias)
{
	this->delVal = x;
	this->bias = bias;
	this->activate(0);
	this->derive(0);
}

Neuron::Neuron(double x)
{ 
	this->delVal = (double)x;
	this->bias = 0;
	this->activate(0);
	this->derive(0);
}
void Neuron::activate(int which_function)
{
	switch (which_function)
	{
	case 0:
		this->actVal = this->sigmoid(this->delVal);
		break;
	case 1:
		this->actVal = this->inverse_sqrt(this->delVal, 1.0);
		break;
	case 2:
		this->actVal = this->relu(this->delVal);
		break;
	case 3:
		this->actVal = this->tanh(this->delVal);
		break;
	case 4:
		this->actVal = this->binary_step(this->delVal);
		break;
	default:
		this->actVal = this->sigmoid(this->delVal);
		break;
	}

}
void Neuron::derive(int which_function)
{
	switch (which_function)
	{
	case 0:
		this->derVal = this->sigmoid_derive(this->delVal);
		break;
	case 1:
		this->derVal = this->inverse_sqrt_derive(this->delVal, 1.0);
		break;
	case 2:
		this->derVal = this->relu_derive(this->delVal);
		break;
	case 3:
		this->derVal = this->tanh_derive(this->delVal);
		break;
	case 4:
		this->derVal = this->binary_step_derive(this->delVal);
		break;
	default:
		this->derVal = this->sigmoid_derive(this->delVal);
		break;
	}
}

// sigmoid and derive
double Neuron::sigmoid(double x) 
{ 
	return 1 / (1 + exp(-x)); 
}
double Neuron::sigmoid_derive(double x)
{ 
	return this->sigmoid(x) * (1 - this->sigmoid(x));
}
// tanh and derive
double Neuron::tanh(double x)
{
	return (exp(x) - exp(-x)) / (exp(x) + exp(-x)); 
}
double Neuron::tanh_derive(double x)
{
	return 1 - pow(this->tanh(x), 2); 
}
// relu and derive
double Neuron::relu(double x) 
{
	return (x < 0) ? 0 : x; 
}
double Neuron::relu_derive(double x) 
{
	return (x > 0) ? 1 : 0;
}
// binary step
double Neuron::binary_step(double x) 
{
	return (x >= 0) ? 1 : 0; 
}
double Neuron::binary_step_derive(double x) 
{
	return 0; 
}
// inverse square root and derive
double Neuron::inverse_sqrt(double x, double a) 
{
	return x / sqrt(1 + a * pow(x, 2));
}
double Neuron::inverse_sqrt_derive(double x, double a) 
{ 
	return pow(1 / sqrt(a*pow(x, 2) + 1), 3);
}
// arcsinh and derive
double Neuron::arsinh(double x) 
{
	return log(x + sqrt(pow(x, 2) + 1)); 
}
double Neuron::arcsinh_derive(double x) 
{
	return 1 / sqrt(pow(x, 2) + 1); 
}


void Neuron::set_val(double x) 
{ 
	this->delVal = x;
	this->activate(0); 
	this->derive(0);
}

void Neuron::set_val(double x, int function)
{
	this->delVal = x;
	this->activate(function);
	this->derive(function);
}
