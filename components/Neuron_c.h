//
// Created by Yorick on 12/11/2016.
//

#ifndef DUNGEONCRAWLERBOTS_NEURON_H
#define DUNGEONCRAWLERBOTS_NEURON_H


#include <vector>

struct Neuron_c {
    Neuron_c();

    std::vector<int> connectedNeuronId;
    std::vector<float> connectedNeuronWeight;

    float bias;
    float output;
};


#endif //DUNGEONCRAWLERBOTS_NEURON_H
