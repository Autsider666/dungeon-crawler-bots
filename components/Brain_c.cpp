//
// Created by Yorick on 12/11/2016.
//

#include <cmath>
#include <iostream>
#include <math.h>
#include "Brain_c.h"
#include "../settings.h"
#include "../rng.h"

Brain_c::Brain_c() {
    for (int i = 0; i < settings::BrainSize; ++i) {
        Neuron_c n;
        neurons.push_back(n);
    }

    output.resize(settings::OutputNeurons, 0);
}

void Brain_c::tick(std::vector<float> &input) {

    for (int i = 0; i < neurons.size(); ++i) {
        Neuron_c *currentNeuron = &neurons[i];

        if (i < settings::InputNeurons) {
            currentNeuron->output = input[i];
        } else {
            float activationValue = currentNeuron->bias;

            for (int j = 0; j < currentNeuron->connectedNeuronId.size(); ++j) {
                int idx = currentNeuron->connectedNeuronId[j];
                activationValue += neurons[idx].output * currentNeuron->connectedNeuronWeight[j];
            }
            currentNeuron->output = 1.0 / (1.0 + exp(-activationValue));;
        }
    }

    for (int k = 0; k < settings::OutputNeurons; ++k) {
        output[k] = neurons[neurons.size() - 1 - k].output;
    }
}

Brain_c Brain_c::reproduce() {
    Brain_c babyBrain;

    babyBrain.neurons = neurons;

    for (int i = 0; i < settings::BrainSize; ++i) {
        if (rng::getRandomFloatBetween(0, 1) < settings::mutationRate) {
            neurons[i].bias += rng::getRandomMutation(settings::mutatuionStrength);
        }
        for (int j = 0; j < neurons[i].connectedNeuronId.size(); ++j) {
            if (rng::getRandomFloatBetween(0, 1) < settings::mutationRate) {
                neurons[i].connectedNeuronWeight[j] += rng::getRandomMutation(settings::mutatuionStrength);
            }
            if (rng::getRandomFloatBetween(0, 1) < settings::mutationRate / 10) {
                neurons[i].connectedNeuronId[j] = rng::getRandomIntBetween(0, settings::BrainSize - 1);
            }
            if (rng::getRandomFloatBetween(0, 1) < settings::mutationRate / 5) {
                neurons[i].connectedNeuronId[j] = rng::getRandomIntBetween(0, settings::BrainSize - 1);
            }
        }
    }

    return babyBrain;
}
