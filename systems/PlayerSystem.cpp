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
            targetPosition->x = rng::getRandomIntBetween(0, Settings::SimulationWidth - 1);
            targetPosition->y = rng::getRandomIntBetween(0, Settings::SimulationHeight - 1);
        }
    }

    int players = 0;

    World *w = Simulation::getInstance()->getWorld();
    w->resetPlayerSoundMap();
    rltk::each<Player_c, Position_c>([&w, &players](rltk::entity_t &entity, Player_c &player, Position_c &pos) {
        players++;
        for (int x = 0; x < Settings::SimulationWidth; ++x) {
            for (int y = 0; y < Settings::SimulationHeight; ++y) {
                float dx = x - pos.x;
                float dy = y - pos.y;
                float strength = Settings::BasicSoundRange * 2 - std::sqrt(dx * dx + dy * dy);
                if (strength > 0 && w->getPlayerSoundAt(x, y) < strength) {
                    w->setPlayerSoundAt(x, y, strength);
                }
            }
        }
    });
    if (players == 0) {
        while (players < Settings::MinimumPlayers) {
            rltk::create_entity()
                    ->assign(Player_c{})
                    ->assign(Position_c{rng::getRandomFloatBetween(0, Settings::SimulationWidth - 1),
                                        rng::getRandomFloatBetween(0, Settings::SimulationHeight - 1)})
                    ->assign(Renderable_c{'@', rltk::colors::YELLOW});
            players++;
        }
    }
}
