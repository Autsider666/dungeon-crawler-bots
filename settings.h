//
// Created by Yorick on 12/11/2016.
//

#ifndef DUNGEONCRAWLERBOTS_SETTINGS_H
#define DUNGEONCRAWLERBOTS_SETTINGS_H

namespace Settings {
    const unsigned SimulationWidth = 54;
    // 108;
    const unsigned SimulationHeight = 48; //96;

    const unsigned MinimumMonsters = 10;
    const unsigned MaximumMonsters = 50;
    const float BasicSoundRange = 20;
    const float BasicHeatRange = 40;

    const unsigned MinimumPlayers = 5;

    const unsigned BrainSize = 50;

    const unsigned Babies = 2;

    const float mutationRate = 0.002f;
    const float mutationStrength = 0.05f;

    const unsigned StartingNeuronConnections = 8;
    const unsigned InputNeurons = 11; //5;
    const unsigned OutputNeurons = 5; //10;
    const float SparceConnectionPercentage = 0.0;
    const float DirectInputConnectChance = 0.5; //0.2;
    const float MinimumWeight = -3;
    const float MaximumWeight = 3;
    const float MinimumBias = -3;
    const float MaximumBias = 3;
}

enum Vision {
    Basic,
    MonsterSound,
    PlayerSound
};

#endif //DUNGEONCRAWLERBOTS_SETTINGS_H
