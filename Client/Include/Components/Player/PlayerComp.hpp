/*
** EPITECH PROJECT, 2024
** PlayerComp.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef PLAYERCOMP_HPP
#define PLAYERCOMP_HPP
#include <ECS/Component.hpp>
#include <SFML/Graphics.hpp>
#include "Components/GUI/SpriteComp.hpp"
#include "PlayerMovementComp.hpp"
#include "PlayerShootComp.hpp"
#include "PlayerForceBar.hpp"

class PlayerComp : public Component {
public:
    PlayerComp(std::string playerName, sf::Texture &texture, bool isLocallyControlled = true);
    void init() override;
    void update(double t, double dt, Manager::PlayerInputs inputs) override;
    void draw() override;
private:
    std::string _playerName;
public:
    bool isLocallyControlled;
    sf::Texture &_texture;
    TransformComp *transform;
    SpriteComp *playerSprite;
    PlayerMovementComp *movement;
    PlayerShootComp *shootComp;
    const std::string &getPlayerName() const;
    void kill();
};

#endif //PLAYERCOMP_HPP
