#pragma once
#include <math.h>
#include<iostream>
using namespace std;
// NEURON AND ITS FUNCTIONS / NEURON I JEGO FUNKCJE
class Neuron
{
private:
	double delVal; // delivered  value / wartosc dostarczona
	double actVal; // activation value / wartosc aktywacji
	double derVal; // derivative value / wartosc pochodnej
	double bias;

public:

	double sigmoid(double x);
	double tanh(double x);
	double relu(double x);
	double binary_step(double x);
	double inverse_sqrt(double x, double a);
	double arsinh(double x);


	double sigmoid_derive(double x);
	double tanh_derive(double x);
	double relu_derive(double x);
	double binary_step_derive(double x);
	double inverse_sqrt_derive(double x, double a);
	double arcsinh_derive(double x);

	void set_val(double x);
	void set_val(double x, int function);
	double get_value() { return this->delVal; }
	double get_avalue() { return this->actVal; }
	double get_dvalue() { return this->derVal; }


	void activate(int which_function);
	void derive(int which_function);

	Neuron(double x);
	Neuron(double x, double bias);
	Neuron(); 

};

