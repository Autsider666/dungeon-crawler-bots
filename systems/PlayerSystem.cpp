//
// Created by Yorick on 16/11/2016.
//

#include "PlayerSystem.h"
#include "../messages/PlayerAttackedMessage.h"
#include "../components/Position_c.h"
#include "../settings.h"
#include "../rng.h"
#include "../components/Player_c.h"
#include "../components/Renderable_c.h"

void PlayerSystem::configure() {
    system_name = "Player System";

    subscribe_mbox<PlayerAttackedMessage>();
}

void PlayerSystem::update(const double duration_ms) {
    std::queue<PlayerAttackedMessage> *messages = mbox<PlayerAttackedMessage>();
    std::vector<size_t> deleted;
    while (!messages->empty()) {
        PlayerAttackedMessage e = messages->front();
        messages->pop();
        if (std::find(deleted.begin(), deleted.end(), e.player->id) == deleted.end()) {
            deleted.push_back(e.player->id);
            auto targetPosition = e.player->component<Position_c>();
            targetPosition->x = rng::getRandomIntBetween(0, settings::SimulationWidth - 1);
            targetPosition->y = rng::getRandomIntBetween(0, settings::SimulationHeight - 1);
        }
    }

    int players = 0;

    rltk::each<Player_c>([&players](rltk::entity_t &entity, Player_c &player) {
        players++;
    });
    if (players == 0) {
        while (players < settings::MinimumPlayers) {
            rltk::create_entity()
                    ->assign(Player_c{})
                    ->assign(Position_c{rng::getRandomFloatBetween(0, settings::SimulationWidth - 1),
                                        rng::getRandomFloatBetween(0, settings::SimulationHeight - 1)})
                    ->assign(Renderable_c{'@', rltk::colors::YELLOW});
            players++;
        }
    }
}
