//
// Created by Yorick on 12/11/2016.
//

#ifndef DUNGEONCRAWLERBOTS_AGENT_C_H
#define DUNGEONCRAWLERBOTS_AGENT_C_H

#include <vector>
#include <string>

struct Monster_c {
    Monster_c();

    float health;
    int age;

    int generation;

    int inactivity;

    float clock1, clock2;

    std::vector<std::string> mutations;

    Monster_c reproduce();

    Monster_c crossover(const Monster_c &other);
};


#endif //DUNGEONCRAWLERBOTS_AGENT_C_H
