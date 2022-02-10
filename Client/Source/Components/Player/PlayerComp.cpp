/*
** EPITECH PROJECT, 2024
** PlayerComp.cpp
** File description:
** Created by Leo Fabre
*/
#include "Components/Player/PlayerComp.hpp"
#include <AssetLoader.hpp>

PlayerComp::PlayerComp(
    std::string playerName, sf::Texture &texture, bool isLocallyControlled
)
    : _playerName(playerName),
      _texture(texture),
      playerSprite(nullptr),
      transform(nullptr),
      movement(nullptr),
      isLocallyControlled(isLocallyControlled)
{
}

void PlayerComp::init()
{
    Component::init();
    if (!entity->hasComponent<TransformComp>()) {
        transform = &entity->addComponent<TransformComp>();
    } else {
        transform = &entity->getComponent<TransformComp>();
    }

    if (!entity->hasComponent<PlayerMovementComp>()) {
        movement =
            &entity->addComponent<PlayerMovementComp>(isLocallyControlled);
    } else {
        movement = &entity->getComponent<PlayerMovementComp>();
    }

    if (!entity->hasComponent<SpriteComp>()) {
        playerSprite =
            &entity->addComponent<SpriteComp>(
                _texture,
                sf::Vector2u{5, 1}, 0, 2
            );
    } else {
        std::cerr << "Player sprite comp already present. skipping"
            << std::endl;
        playerSprite = &entity->getComponent<SpriteComp>();
    }

    if (!entity->hasComponent<PlayerShootComp>()) {
        shootComp =
            &entity->addComponent<PlayerShootComp>(getPlayerName(),
                isLocallyControlled, entity->assets()->shoot);
    } else {
        shootComp = &entity->getComponent<PlayerShootComp>();
    }
    auto playerBounds =
        entity->getComponent<SpriteComp>().sprite.getLocalBounds();
}

const std::string &PlayerComp::getPlayerName() const
{
    return _playerName;
}

void PlayerComp::update(double t, double dt, Manager::PlayerInputs inputs)
{
    Component::update(t, dt, inputs);
}

void PlayerComp::draw()
{
    Component::draw();
}

void PlayerComp::kill()
{
    movement->blockInputs();
    shootComp->active = false;
    playerSprite->sprite.setScale(0, 0);
}
