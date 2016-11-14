//
// Created by Yorick on 12/11/2016.
//

#include "Neuron_c.h"
#include "../settings.h"
#include "../rng.h"

Neuron_c::Neuron_c() {
    connectedNeuronId.resize(settings::StartingNeuronConnections,0);
    connectedNeuronWeight.resize(settings::StartingNeuronConnections,0);

    for (int i = 0; i < settings::StartingNeuronConnections; ++i) {
        if (rng::getRandomFloatBetween(0,1)<settings::SparceConnectionPercentage) {
            connectedNeuronWeight[i] = 0; // neutralize neuron connection (sparse)
        } else {
            connectedNeuronWeight[i] = rng::getRandomFloatBetween(settings::MinimumWeight,settings::MaximumWeight);
        }

        if (rng::getRandomFloatBetween(0,1)<settings::DirectInputConnectChance) { //
            connectedNeuronId[i] = rng::getRandomIntBetween(0,settings::InputNeurons); // percentage guaranteed connection with input nodes
        } else {
            connectedNeuronId[i] = rng::getRandomIntBetween(0,settings::BrainSize);
        }
    }
    bias = rng::getRandomFloatBetween(settings::MinimumBias,settings::MaximumBias);
    output = 0;
}
