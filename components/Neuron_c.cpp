//
// Created by Yorick on 12/11/2016.
//

#include "Neuron_c.h"
#include "../settings.h"
#include "../rng.h"

Neuron_c::Neuron_c() {
    connectedNeuronId.resize(Settings::StartingNeuronConnections,0);
    connectedNeuronWeight.resize(Settings::StartingNeuronConnections,0);

    for (int i = 0; i < Settings::StartingNeuronConnections; ++i) {
        if (rng::getRandomFloatBetween(0,1)< Settings::SparceConnectionPercentage) {
            connectedNeuronWeight[i] = 0; // neutralize neuron connection (sparse)
        } else {
            connectedNeuronWeight[i] = rng::getRandomFloatBetween(Settings::MinimumWeight, Settings::MaximumWeight);
        }

        if (rng::getRandomFloatBetween(0,1)< Settings::DirectInputConnectChance) { //
            connectedNeuronId[i] = rng::getRandomIntBetween(0, Settings::InputNeurons); // percentage guaranteed connection with input nodes
        } else {
            connectedNeuronId[i] = rng::getRandomIntBetween(0, Settings::BrainSize);
        }
    }
    bias = rng::getRandomFloatBetween(Settings::MinimumBias, Settings::MaximumBias);
    output = 0;
}
