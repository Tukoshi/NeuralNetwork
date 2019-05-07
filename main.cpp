#include "NeuralNet.h"
#include <vector>

int main()
{	// topologia sieci i wartosci wejsciowe
	vector<int> topology = { 1, 1, 1, 1, 1, 1 };
	vector<double> input = {66666.5};
	// stworz siec, daj wartosci na input, wlacz 
	NeuralNet * siec1 = new NeuralNet(topology);

	siec1->setCurrentInput(input);


	siec1->feedforward(0);
	siec1->layers.at(5)->print_layer(1);
	siec1->feedforward(1);
	siec1->layers.at(5)->print_layer(1);
	siec1->feedforward(2);
	siec1->layers.at(5)->print_layer(1);
	siec1->feedforward(3);
	siec1->layers.at(5)->print_layer(1);
	siec1->feedforward(4);
	siec1->layers.at(5)->print_layer(1);
	siec1->feedforward(5);
	siec1->layers.at(5)->print_layer(1);



	







	delete siec1;
	return 0;
}

