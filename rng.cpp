//
// Created by Yorick on 10/11/2016.
//

#include <time.h>
#include "rng.h"
#include "settings.h"

using namespace std;

rng *rng::_instance = nullptr;

rng::rng() {
    _gen.seed(time(NULL));
}

rng *rng::getInstance() {
    if (!_instance)
        _instance = new rng();
    return _instance;
}

signed int rng::roleDice(int size, int amount) {
    uniform_int_distribution<> dis(1, size);
    signed int result = 0;
    for (int i = 0; i < amount; ++i) {
        result += dis(getInstance()->_gen);
    }

    return result;
}

signed int rng::getRandomIntBetween(float min, float max) {
    if (min < max) {
        uniform_int_distribution<> dis(min, max);
        return dis(getInstance()->_gen);
    }
    return 0;
}

signed int rng::getRandomIntBetween(int min, int max) {
    if (min < max) {
        uniform_int_distribution<> dis(min, max);
        return dis(getInstance()->_gen);
    }
    return 0;
}

float rng::getRandomFloatBetween(float min, float max) {
    if (min < max) {
        uniform_real_distribution<float> dis(min, max);
        return dis(getInstance()->_gen);
    }
    return 0;
}

float rng::getRandomFloatBetween(int min, int max) {
    if (min < max) {
        uniform_real_distribution<float> dis(min, max);
        return dis(getInstance()->_gen);
    }
    return 0;
}

float rng::getRandomMutation(float chance) {
    float val = getRandomFloatBetween(0, 1) * chance * 2 - chance;

    return val;
}
