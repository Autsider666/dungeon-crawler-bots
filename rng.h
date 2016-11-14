//
// Created by Yorick on 10/11/2016.
//

#ifndef SOLOMON_RNG_H
#define SOLOMON_RNG_H


#include <random>

class rng {
    rng();

    static rng *_instance;

    std::mt19937 _gen;

    static rng *getInstance();

public:

    static signed int roleDice(int size, int amount = 1);

    static signed int getRandomIntBetween(int min, int max);

    static float getRandomFloatBetween(float min, float max);

    static float getRandomFloatBetween(int min, int max);

    static float getRandomMutation(float chance);
};


#endif //SOLOMON_RNG_H
