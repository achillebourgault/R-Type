/*
** EPITECH PROJECT, 2024
** ExplosionFxComp.cpp
** File description:
** Created by Leo Fabre
*/
#include "ECS/Entity.hpp"
#include "ExplosionFxComp.hpp"
#include <AssetLoader.hpp>

ExplosionFXComp::ExplosionFXComp(sf::Vector2f position) : basePos(position)
{

}

void ExplosionFXComp::init()
{
    Component::init();
    entity->addGroup(GroupLabel::GUI_TOP);
    if (!entity->hasComponent<TransformComp>()) {
        transform = &entity->addComponent<TransformComp>();
        transform->position = basePos;
        transform->position += {33 / 2, 36 / 2};
    }
    sprite_component = &entity->addComponent<SpriteComp>(
        entity->assets()->Explosion,
        sf::Vector2u (6,1)
        );
}

void ExplosionFXComp::update(double t, double dt, Manager::PlayerInputs inputs)
{
    Component::update(t, dt, inputs);
    if (sprite_component->lineDone) {
        sprite_component->sprite.setScale(0, 0);
        entity->destroy();
    }
}
