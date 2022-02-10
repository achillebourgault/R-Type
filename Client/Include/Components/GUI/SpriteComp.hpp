/*
** EPITECH PROJECT, 2024
** SpriteComp.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef SPRITECOMP_HPP
#define SPRITECOMP_HPP

#include <ECS/Component.hpp>
#include <SFML/Graphics.hpp>
#include "TransformComp.hpp"

class SpriteComp : public Component {
public:
    SpriteComp(
        std::string texturePath, sf::Vector2u nbReps,
        float updateTimeMilliSeconds = 50.f, float scale = 1.f,
        sf::IntRect subSprite =
        {-667,0,0,0}
    );
    SpriteComp(
        const sf::Texture& texture, sf::Vector2u nbReps,
        float updateFrequency = 0.5f, float scale = 1.f
    );
    void init() override;
    void update(double t, double dt, Manager::PlayerInputs inputs) override;
    void draw() override;

    sf::Texture texture;
    sf::Sprite sprite;

    sf::Vector2u _rectSize, _nbReps;
    sf::IntRect spriteRect;
    sf::Clock clock;
    sf::Time timer;
    sf::Time updateFrequency;
    void setSpriteNextFrame();
    void setSpriteFrame(uint frameNumber);
    TransformComp *transform;
    bool lineDone = false;
};

#endif //SPRITECOMP_HPP
