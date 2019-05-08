#pragma once
#include <math.h>
#include<iostream>
using namespace std;

class Activators
{
public:
	double a;
	Activators::Activators() { a = 1.0; }
	Activators::Activators(double a) { this->a = a; }

	double activate(int function, double value)
	{
		double actValue;
		switch (function)
		{
		default:
		case 1:
			actValue = identity(value);
			break;
 		case 2:
			actValue = binary_step(value);
			break;
		case 3:
			actValue = sigmoid(value);
			break;
		case 4:
			actValue = tanh(value);
			break;
		case 5:
			actValue = ArcTan(value);
			break;
		case 6:
			actValue = arsinh(value);
			break;
		case 7:
			actValue = Softsign(value);
			break;
		case 8:
			actValue = isru(value, a);
			break;
		case 9:
			actValue = isrlu(value,a);
			break;
		case 10:
			actValue = SQNL(value);
			break;
		case 11:
			actValue = relu(value);
			break;
		case 12:
			actValue = prelu(value, a);
			break;
		case 13:
			actValue = elu(value, a);
			break;
		case 14:
			actValue = softplus(value);
			break;
		case 15:
			actValue = bent_identity(value);
			break;
		case 16:
			actValue = softExpotential(value, a);
			break;
		case 17:
			actValue = sinc(value);
			break;
		case 18:
			actValue = gaussian(value);
			break;
		}
		return actValue;
	}
	double derive(int function, double value, double a = 1)
	{
		double derValue;
		switch (function)
		{
		default:

		case 1:
			derValue = identity_derive(value);
			break;
		case 2:
 			derValue = binary_step_derive(value);
			break;
		case 3:
 			derValue = sigmoid_derive(value);
			break;
		case 4:
 			derValue = tanh_derive(value);
			break;
		case 5:
 			derValue = ArcTan_derive(value);
			break;
		case 6:
 			derValue = arsinh_derive(value);
			break;
		case 7:
			derValue = Softsign_derive(value);
			break;
		case 8:
			derValue = isru_derive(value, a);
			break;
		case 9:
			derValue = isrlu_derive(value, a);
			break;
		case 10:
			derValue = SQNL_derive(value);
			break;
		case 11:
			derValue = relu_derive(value);
			break;
		case 12:
			derValue = prelu_derive(value, a);
			break;
		case 13:
			derValue = elu_derive(value, a);
			break;
		case 14:
			derValue = softplus_derive(value);
			break;
		case 15:
			derValue = bent_identity_derive(value);
			break;
		case 16:
			derValue = softExpotential_derive(value, a);
			break;
		case 17:
			derValue = sinc_derive(value);
			break;
		case 18:
			derValue = gaussian_derive(value);
			break;
		}
		return derValue;
	}




	// #1
	double identity(double x)
	{
		return x;
	}
	double identity_derive(double x)
	{
		return 1;
	}
	// #2
	double binary_step(double x)
	{
		return (x >= 0) ? 1 : 0;
	}
	double binary_step_derive(double x)
	{
		return 0;
	}
	// #3
	double sigmoid(double x)
	{
		return 1 / (1 + exp(-x));
	}
	double sigmoid_derive(double x)
	{
		return this->sigmoid(x) * (1 - this->sigmoid(x));
	}
	// #4
	double tanh(double x)
	{
		return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
	}
	double tanh_derive(double x)
	{
		return 1 - pow(this->tanh(x), 2);
	}
	// #5
	double ArcTan(double x)
	{
		return atan(x);
	}
	double ArcTan_derive(double x)
	{
		return 1 / (pow(x, 2) + 1);
	}
	// #6
	double arsinh(double x)
	{
		return log(x + sqrt(pow(x, 2) + 1));
	}
	double arsinh_derive(double x)
	{
		return 1 / sqrt(pow(x, 2) + 1);
	}
	// #7
	double Softsign(double x)
	{
		return x / (1 + abs(x));
	}
	double Softsign_derive(double x)
	{
		return 1 / pow(1 + abs(x), 2);
	}
	// #8
	double isru(double x, double a)
	{
		return x / sqrt(1 + a * pow(x, 2));
	}
	double isru_derive(double x, double a)
	{
		return pow(1 / sqrt(a*pow(x, 2) + 1), 3);
	}
	// #9
	double isrlu(double x, double a)
	{
		if (x < 0) return x / sqrt(1 + a * pow(x, 2));
		else return x;
	}
	double isrlu_derive(double x, double a)
	{
		if (x < 0) return x / sqrt(1 + a * pow(x, 2));
		else return x;
	}
	// #10
	double SQNL(double x)
	{
		if (x >= 2.0)
		{
			return 1;
		}
		else if (x >= 0.0 && x < 2.0)
		{
			return x - (pow(x, 2) / 4);
		}
		else if (x >= -2.0 && x < 0.0)
		{
			return x + (pow(x, 2) / 4);
		}
		else
		{
			return -1;
		}
	}
	double SQNL_derive(double x)
	{
		if (x >= 0.0)
		{
			return 1 + x / 2;
		}

		else
		{
			return 1 - x / 2;
		}
	}
	// #11
	double relu(double x)
	{
		return (x < 0) ? 0 : x;
	}
	double relu_derive(double x)
	{
		return (x > 0) ? 1 : 0;
	}
	// #12
	double prelu(double x, double a)
	{
		if (x >= 0)
		{
			return a * x;
		}
		else
		{
			return x;
		}
	}
	double prelu_derive(double x, double a)
	{
		if (x >= 0)
		{
			return a;
		}
		else
		{
			return 1;
		}
	}
	// #13
	double elu(double x, double a)
	{
		if (x >= 0)
		{
			return a * (exp(x) - 1);
		}
		else
		{
			return x;
		}
	}
	double elu_derive(double x, double a)
	{
		if (x >= 0)
		{
			return this->elu(x, a) + a;
		}
		else
		{
			return 1;
		}
	}
	// #14
	double softplus(double x)
	{
		return log(1 + exp(x));
	}
	double softplus_derive(double x)
	{
		return this->sigmoid(x);
	}
	// #15
	double bent_identity(double x)
	{
		return ((sqrt(pow(x, 2) + 1) - 1) / 2) + x;
	}
	double bent_identity_derive(double x)
	{
		return x / (2 * sqrt(pow(x, 2) + 1)) + 1;
	}
	// #16
	double softExpotential(double x, double a)
	{
		if (a > 0)
		{
			return (-1 / a) * log(1 - a * (x + a));
		}
		else if (a == 0)
		{
			return x;
		}
		else
		{
			return (1 / a)*(exp(a*x) - 1) + a;
		}
	}
	double softExpotential_derive(double x, double a)
	{
		if (a >= 0)
		{
			return exp(a*x);
		}

		else
		{
			return 1 / (1 - a * (a + x));
		}
	}
	// #17
	double sinc(double x)
	{
		if (x == 0) return 1;
		else
		{
			return sin(x) / x;
		}
	}
	double sinc_derive(double x)
	{
		if (x == 0) return 0;
		else
		{
			return (cos(x) / x) - (sin(x) / pow(x, 2));
		}
	}
	// #18
	double gaussian(double x)
	{
		return exp(-pow(x, 2));
	}
	double gaussian_derive(double x)
	{
		return -2 * x * this->gaussian(x);
	}
};
// NEURON AND ITS FUNCTIONS / NEURON I JEGO FUNKCJE
class Neuron
{
private:
	double delVal; // delivered  value / wartosc dostarczona
	double actVal; // activation value / wartosc aktywacji
	double derVal; // derivative value / wartosc pochodnej

public:
	
	double get_value() { return this->delVal; }
	double get_avalue() { return this->actVal; }
	double get_dvalue() { return this->derVal; }

	void setvalue(double value, int function, double a);
	void setvalue(double value, int function);
	void setvalue(double value);
	
	void activate(int function, double a);
	void activate(int function);
	void activate();

	Neuron(double x, int function, double a);
	Neuron(double x, int function);
	Neuron(double x);
	Neuron();
	
	void print();
};
