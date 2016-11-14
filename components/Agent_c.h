//
// Created by Yorick on 12/11/2016.
//

#ifndef DUNGEONCRAWLERBOTS_AGENT_C_H
#define DUNGEONCRAWLERBOTS_AGENT_C_H

#include <vector>
#include <string>

struct Agent_c {
    Agent_c();

    int fitness;
    float health;
    int age;

    int generation;

    float clock1, clock2;

    std::vector<std::string> mutations;

    Agent_c reproduce();
};


#endif //DUNGEONCRAWLERBOTS_AGENT_C_H
