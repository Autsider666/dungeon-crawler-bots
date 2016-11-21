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
#include "../World.h"
#include "../Simulation.h"
#include "../utility/navigator_helper.h"
#include "../external/rltk/rltk/visibility.hpp"
#include "../external/rltk/rltk/path_finding.hpp"
#include "../components/HeatSource_c.h"

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
        }
    }

    for (size_t id : deleted) {
        rltk::delete_entity(id);
    }

    int players = 0;

    rltk::each<Player_c, Position_c>([&players](rltk::entity_t &entity, Player_c &player, Position_c &pos) {
        players++;
    });

    while (players < Settings::MinimumPlayers) {
        int x = rng::getRandomIntBetween(0, Settings::SimulationWidth - 1);
        int y = rng::getRandomIntBetween(0, Settings::SimulationHeight - 1);

        if (Simulation::getInstance()->getWorld()->isWalkableAt(x, y)) {
            rltk::create_entity()
                    ->assign(Player_c{})
                    ->assign(Position_c{x, y})
                    ->assign(HeatSource_c{Settings::BasicHeatRange})
                    ->assign(Renderable_c{'@', rltk::colors::YELLOW});
            players++;
        }
    }
}
