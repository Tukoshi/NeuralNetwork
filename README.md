# NeuralNetwork
Basic Neural network 

There is implemented:
- single neuron with 18 activation functions (no memory leaks)
- layer of neurons (no memory leaks)
- simple matrix that was used for multiplication (may cause memory leaks - you need to remember to deallocate memory)
- neural network with:
  - simple calculation error (needs to be rebuild)
  - feedforward algorithm (no memory leaks)
  - backpropagation algorith (no memory leaks)

This simple neural network is inspired by this series:
https://youtu.be/PQo78WNGiow
There is LOTS of memory leaks in first implementation of NN in this series(author made another video where he refactors it)
that I took care of and avoided in my implementation. 
