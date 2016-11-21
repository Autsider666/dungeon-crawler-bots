//
// Created by Yorick on 12/11/2016.
//

#include "Monster_c.h"
#include "../rng.h"
#include "../settings.h"

Monster_c::Monster_c() : health(1.0), age(0), generation(0), inactivity(0) {
    clock1 = rng::getRandomFloatBetween(5, 100);
    clock2 = rng::getRandomFloatBetween(5, 100);
}

Monster_c Monster_c::reproduce() {
    Monster_c baby;

    if (rng::getRandomFloatBetween(0, 1) < Settings::mutationRate * 5) {
        baby.clock1 += rng::getRandomMutation(Settings::mutationStrength);
        if (baby.clock1 < 5) {
            baby.clock1 = 5;
        } else if (baby.clock1 > 100) {
            baby.clock1 = 100;
        }
    }

    if (rng::getRandomFloatBetween(0, 1) < Settings::mutationRate * 5) {
        baby.clock2 += rng::getRandomMutation(Settings::mutationStrength);
        if (baby.clock2 < 5) {
            baby.clock2 = 5;
        } else if (baby.clock2 > 100) {
            baby.clock2 = 100;
        }
    }
    return baby;
}

Monster_c Monster_c::crossover(const Monster_c &other) {
    Monster_c baby;

    baby.clock1 = rng::getRandomFloatBetween(0, 1) < 0.5 ? this->clock1 : other.clock1;
    baby.clock2 = rng::getRandomFloatBetween(0, 1) < 0.5 ? this->clock2 : other.clock2;

    return baby;
}
