//
// Created by Yorick on 16/11/2016.
//

#include "InputSystem.h"
#include "../external/rltk/rltk/input_handler.hpp"
#include "../external/rltk/rltk/rltk.hpp"
#include "../Simulation.h"

using namespace rltk;

void InputSystem::configure() {
    system_name = "Input System";

    subscribe_mbox<key_pressed_t>();
}

void InputSystem::update(const double duration_ms) {
    std::queue<key_pressed_t> *messages = mbox<key_pressed_t>();
    while (!messages->empty()) {
        key_pressed_t e = messages->front();
        messages->pop();

        if (e.event.key.code == sf::Keyboard::Num0) get_window()->setFramerateLimit(1000);
        if (e.event.key.code == sf::Keyboard::Num1) get_window()->setFramerateLimit(10);
        if (e.event.key.code == sf::Keyboard::Num2) get_window()->setFramerateLimit(20);
        if (e.event.key.code == sf::Keyboard::Num3) get_window()->setFramerateLimit(30);
        if (e.event.key.code == sf::Keyboard::Num4) get_window()->setFramerateLimit(40);
        if (e.event.key.code == sf::Keyboard::Num5) get_window()->setFramerateLimit(50);
        if (e.event.key.code == sf::Keyboard::Numpad0) Simulation::getInstance()->setRenderMode(0);
        if (e.event.key.code == sf::Keyboard::Numpad1) Simulation::getInstance()->setRenderMode(1);
        if (e.event.key.code == sf::Keyboard::Numpad2) Simulation::getInstance()->setRenderMode(2);
        if (e.event.key.code == sf::Keyboard::Numpad3) Simulation::getInstance()->setRenderMode(3);
        if (e.event.key.code == sf::Keyboard::Numpad4) Simulation::getInstance()->setRenderMode(4);
        if (e.event.key.code == sf::Keyboard::F1) {
            std::string timings = ecs_profile_dump();
            std::cout << timings << "\n";
        }
    }
}
