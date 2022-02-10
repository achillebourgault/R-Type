/*
** EPITECH PROJECT, 2024
** AudioComp.hpp
** File description:
** Created by Achille Bourgault
*/

#ifndef AudioComp_HPP
#define AudioComp_HPP

#include <GUI/TextComp.hpp>
#include <GUI/SpriteComp.hpp>
#include <SFML/Audio.hpp>
#include "SFML/Graphics.hpp"
#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"
#include "ECS/Manager.hpp"
#include "TransformComp.hpp"
#include "Components/GUI/SubPanelComp.hpp"

class AudioComp : public Component {
public:
    explicit AudioComp(sf::Sound audioFile, bool repeated = false);
    void draw() override;
    void init() override;
    void update(double t, double dt, Manager::PlayerInputs inputs) override;

    sf::Sound audioFile;
    bool repeated;
    bool hasEverPlayed = false;
};

#endif //AudioComp_HPP
