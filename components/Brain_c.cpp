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
    for (int i = 0; i < Settings::BrainSize; ++i) {
        Neuron_c n;
        neurons.push_back(n);
    }

    output.resize(Settings::OutputNeurons, 0);
}

void Brain_c::tick(std::vector<float> input) {

    for (int i = 0; i < neurons.size(); ++i) {
        Neuron_c *currentNeuron = &neurons[i];

        if (i < Settings::InputNeurons) {
            currentNeuron->output = input[i];
        } else {
            float activationValue = currentNeuron->bias;

            for (int j = 0; j < currentNeuron->connectedNeuronId.size(); ++j) {
                int idx = currentNeuron->connectedNeuronId[j];
                activationValue += neurons[idx].output * currentNeuron->connectedNeuronWeight[j];
            }
            currentNeuron->output = 1.0 / (1.0 + exp(-activationValue));
        }
    }

    for (int k = 0; k < Settings::OutputNeurons; ++k) {
        output[k] = neurons[neurons.size() - 1 - k].output;
    }
}

Brain_c Brain_c::reproduce() {
    Brain_c babyBrain;

    babyBrain.neurons = neurons;

    for (int i = 0; i < Settings::BrainSize; ++i) {
        if (rng::getRandomFloatBetween(0, 1) < Settings::mutationRate) {
            neurons[i].bias += rng::getRandomMutation(Settings::mutationStrength);
        }
        for (int j = 0; j < neurons[i].connectedNeuronId.size(); ++j) {
            if (rng::getRandomFloatBetween(0, 1) < Settings::mutationRate) {
                neurons[i].connectedNeuronWeight[j] += rng::getRandomMutation(Settings::mutationStrength);
            }
            if (rng::getRandomFloatBetween(0, 1) < Settings::mutationRate / 5) {
                neurons[i].connectedNeuronId[j] = rng::getRandomIntBetween(0, Settings::BrainSize - 1);
            }
        }
    }
    return babyBrain;
}

Brain_c Brain_c::crossover(const Brain_c &other) {
    Brain_c babyBrain;

    for (int i = 0; i < Settings::BrainSize; ++i) {
        if (rng::getRandomFloatBetween(0, 1) < 0.5) {
            babyBrain.neurons[i].bias = this->neurons[1].bias;
            for (int j = 0; j < babyBrain.neurons[i].connectedNeuronId.size(); ++j) {
                babyBrain.neurons[i].connectedNeuronId[j] = this->neurons[i].connectedNeuronId[j];
                babyBrain.neurons[i].connectedNeuronWeight[j] = this->neurons[i].connectedNeuronWeight[j];
            }
        } else {
            babyBrain.neurons[i].bias = other.neurons[1].bias;
            for (int j = 0; j < babyBrain.neurons[i].connectedNeuronId.size(); ++j) {
                babyBrain.neurons[i].connectedNeuronId[j] = other.neurons[i].connectedNeuronId[j];
                babyBrain.neurons[i].connectedNeuronWeight[j] = other.neurons[i].connectedNeuronWeight[j];
            }
        }
    }
    return babyBrain;

}
