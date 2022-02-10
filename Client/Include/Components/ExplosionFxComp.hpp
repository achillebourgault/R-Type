/*
** EPITECH PROJECT, 2024
** ExplosionFxComp.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef EXPLOSIONFXCOMP_HPP
#define EXPLOSIONFXCOMP_HPP
#include <ECS/Component.hpp>
#include "GUI/SpriteComp.hpp"

class ExplosionFXComp : public Component {
public:
    void init() override;
    ExplosionFXComp(sf::Vector2f position);
    void update(double t, double dt, Manager::PlayerInputs inputs) override;
    SpriteComp *sprite_component;
    sf::Vector2f basePos;
    TransformComp *transform;
};

#endif //EXPLOSIONFXCOMP_HPP
