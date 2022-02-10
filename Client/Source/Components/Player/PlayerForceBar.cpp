/*
** EPITECH PROJECT, 2024
** PlayerForceBar.cpp
** File description:
** Created by Leo Fabre
*/
#include "Components/Player/PlayerForceBar.hpp"
#include <ECS/Entity.hpp>
#include <ECS/Manager.hpp>

void PlayerForceBar::init()
{
    Component::init();
    shoot_comp =
        &entity->_mgr.getEntByName("Player")
            ->getComponent<PlayerShootComp>();
    auto winSize = entity->_mgr.mainWindow.getSize();
    sf::Vector2f pos(300, (float) (winSize.y - barHeight) - 20);
    sf::Vector2f bgSize(barLength, barHeight);
    sf::Vector2f fillSize(barLength, barHeight-1);

    BackgroundRect.setPosition(pos);
    BackgroundRect.setSize(bgSize);
    BackgroundRect.setFillColor(sf::Color::White);

    // diagonally offset force fill rect for a modest stylish effect
    pos.x++; pos.y++;
    CurrentForceRect.setPosition(pos);
    CurrentForceRect.setSize(fillSize);
    CurrentForceRect.setFillColor(sf::Color(99, 82, 199));
}

void PlayerForceBar::update(double t, double dt, Manager::PlayerInputs inputs)
{
    double forceLength = barLength * (shoot_comp->getShootForce() / 100);
    sf::Vector2f fillSize((float)forceLength - 2, barHeight);
    CurrentForceRect.setSize(fillSize);

    if ((forceLength / 6) >= (100 / 6) * 6) {
        CurrentForceRect.setFillColor(sf::Color(199, 86, 82));
    } else if ((forceLength / 6) >= (100 / 6) * 5) {
        CurrentForceRect.setFillColor(sf::Color(199, 117, 82));
    } else if ((forceLength / 6) >= (100 / 6) * 4) {
        CurrentForceRect.setFillColor(sf::Color(199, 189, 82));
    } else if ((forceLength / 6) >= (100 / 6) * 3) {
        CurrentForceRect.setFillColor(sf::Color(82, 199, 133));
    } else if ((forceLength / 6) >= (100 / 6) * 2) {
        CurrentForceRect.setFillColor(sf::Color(82, 111, 199));
    } else {
        CurrentForceRect.setFillColor(sf::Color(99, 82, 199));
    }
    Component::update(t, dt, inputs);
}

void PlayerForceBar::draw()
{
    Component::draw();
    entity->_mgr.mainWindow.draw(BackgroundRect);
    entity->_mgr.mainWindow.draw(CurrentForceRect);
}
