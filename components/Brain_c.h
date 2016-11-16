//
// Created by Yorick on 12/11/2016.
//

#ifndef DUNGEONCRAWLERBOTS_BRAIN_H
#define DUNGEONCRAWLERBOTS_BRAIN_H


#include <vector>
#include "Neuron_c.h"

struct Brain_c {
    Brain_c();

    std::vector<Neuron_c> neurons;
    std::vector<float> output;

    void tick(std::vector<float> &input);

    Brain_c reproduce();

    Brain_c crossover(const Brain_c & other);
};


#endif //DUNGEONCRAWLERBOTS_BRAIN_H
