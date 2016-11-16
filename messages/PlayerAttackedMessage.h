//
// Created by Yorick on 16/11/2016.
//

#ifndef DUNGEONCRAWLERBOTS_PLAYERATTACKEDMESSAGE_H
#define DUNGEONCRAWLERBOTS_PLAYERATTACKEDMESSAGE_H

#include "../external/rltk/rltk/ecs.hpp"

struct PlayerAttackedMessage : rltk::base_message_t {
    PlayerAttackedMessage() {}
    PlayerAttackedMessage(boost::optional<rltk::entity_t &> attacker,boost::optional<rltk::entity_t &> player) :
            attacker(attacker), player(player) {}

    boost::optional<rltk::entity_t &> attacker;
    boost::optional<rltk::entity_t &> player;
};

#endif //DUNGEONCRAWLERBOTS_PLAYERATTACKEDMESSAGE_H
