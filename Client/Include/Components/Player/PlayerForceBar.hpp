/*
** EPITECH PROJECT, 2024
** PlayerForceBar.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef PLAYERFORCEBAR_HPP
#define PLAYERFORCEBAR_HPP
#include <ECS/Component.hpp>
#include <SFML/Graphics.hpp>
#include "PlayerShootComp.hpp"

class PlayerForceBar : public Component {
public:
    PlayerForceBar() : shoot_comp(nullptr),
                       BackgroundRect(),
                       CurrentForceRect(),
                       barHeight(30),
                       barLength(600)
    {
    }
    void init() override;
    void update(double t, double dt, Manager::PlayerInputs inputs) override;
    void draw() override;
private:
    PlayerShootComp *shoot_comp;
    sf::RectangleShape BackgroundRect;
    sf::RectangleShape CurrentForceRect;
    float barHeight = 30;
    float barLength = 600;
};

#endif //PLAYERFORCEBAR_HPP
