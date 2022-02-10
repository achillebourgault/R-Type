/*
** EPITECH PROJECT, 2024
** SpriteComp.cpp
** File description:
** Created by Leo Fabre
*/
#include "Components/GUI/SpriteComp.hpp"
#include <ECS/Entity.hpp>
#include <ECS/Manager.hpp>

SpriteComp::SpriteComp(
    std::string texturePath, sf::Vector2u nbReps,
    float updateTimeMilliSeconds, float scale, sf::IntRect subSprite
)
    : _nbReps(nbReps),
      sprite(),
      updateFrequency(sf::seconds(updateTimeMilliSeconds))
{
    if (subSprite != sf::IntRect{-667, 0, 0, 0}) {
        if (!texture.loadFromFile(texturePath, subSprite)) {
            std::cerr << "couldn't load subTexture at" << texturePath
                << std::endl;
        }
        std::cout << "SUBSPRITE" << std::endl;
    } else if (!texture.loadFromFile(texturePath)) {
        std::cerr << "couldn't load Texture at" << texturePath << std::endl;
    }
    _rectSize =
        {
            subSprite.width / nbReps.x,
            subSprite.height / nbReps.y
        };
    sprite.setTexture(texture);
    spriteRect = {0, 0, (int) _rectSize.x, (int) _rectSize.y};
    sprite.setTextureRect(spriteRect);
    sprite.setScale(scale, scale);
}

SpriteComp::SpriteComp(
    const sf::Texture &texture, sf::Vector2u nbReps,
    float updateTimeMilliSeconds,
    float scale
)
    : texture(texture),
      _nbReps(nbReps),
      sprite(texture),
      updateFrequency(sf::seconds(updateTimeMilliSeconds))
{
    _rectSize =
        {
            texture.getSize().x / nbReps.x,
            texture.getSize().y / nbReps.y
        };
    spriteRect = {0, 0, (int) _rectSize.x, (int) _rectSize.y};
    sprite.setTextureRect(spriteRect);
    sprite.setScale(scale, scale);
}

void SpriteComp::init()
{
    Component::init();

    if (!entity->hasComponent<TransformComp>()) {
        transform = &entity->addComponent<TransformComp>();
    } else {
        transform = &entity->getComponent<TransformComp>();
    }
    sprite.setPosition(transform->position);
}

void SpriteComp::update(double t, double dt, Manager::PlayerInputs inputs)
{
    Component::update(t, dt, inputs);
    sprite.setPosition(transform->position);
    if (updateFrequency.asSeconds() <= 0) return;
    timer += clock.getElapsedTime();
    if (timer >= updateFrequency) {
        setSpriteNextFrame();
        timer = sf::Time();
        clock.restart();
    }
}

void SpriteComp::draw()
{
    Component::draw();
    sprite.setPosition(transform->position);
    entity->_mgr.mainWindow.draw(sprite);
}

void SpriteComp::setSpriteNextFrame()
{
    int leftMost =
        _rectSize.x * _nbReps.x; //last repetition on line's rect.left
    int topMost = _rectSize.y * _nbReps.y; //top of last line

    spriteRect.left += (int) _rectSize.x;
    if (spriteRect.left >= leftMost) { //end of cur line
        spriteRect.left = 0;
        spriteRect.top += (int) _rectSize.y;
        lineDone = true;
    }
    if (spriteRect.top >= topMost) spriteRect.top = 0; //end of lines

    sprite.setTextureRect(spriteRect);
}

void SpriteComp::setSpriteFrame(uint frameNumber)
{
    int leftMost =
        _rectSize.x * _nbReps.x; //last repetition on line's rect.left
    int topMost = _rectSize.y * _nbReps.y; //top of last line

    spriteRect.left = 0;
    spriteRect.top = 0;
    for (int i = 0; i < frameNumber; ++i) {
        spriteRect.left += (int) _rectSize.x;
        if (spriteRect.left >= leftMost) { //end of cur line
            spriteRect.left = 0;
            spriteRect.top += (int) _rectSize.y;
        }
        if (spriteRect.top >= topMost) spriteRect.top = 0; //end of lines

    }
    sprite.setTextureRect(spriteRect);
}