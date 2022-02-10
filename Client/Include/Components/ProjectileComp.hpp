/*
** EPITECH PROJECT, 2024
** ProjectileComp.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef PROJECTILECOMP_HPP
#define PROJECTILECOMP_HPP

#include <ECS/Component.hpp>
#include <SFML/System/Vector2.hpp>
#include <ECS/Manager.hpp>
#include "Components/GUI/SpriteComp.hpp"

class ProjectileComp : public Component {
public:
    ProjectileComp(
        sf::Texture &sprite, sf::Vector2i direction,
        float speed, sf::Vector2u nb_reps, float update_freq, float scale,
        unsigned int type = 0, int shotBy = -1
    );
    void init() override;
    void update(double t, double dt, Manager::PlayerInputs inputs) override;
    void draw() override;
    SpriteComp *projectileSprite;
    TransformComp *transform;
    sf::Vector2f spawnPos;
    sf::Vector2i direction;
    float speed;
    unsigned int type;
private:
    sf::Texture &_texture;
    sf::Vector2u nbReps;
    float updateFreq;
    float scale;
    int shotBy;
    void CheckMonsters();
};

#endif //PROJECTILECOMP_HPP
