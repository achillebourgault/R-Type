/*
** EPITECH PROJECT, 2024
** PlayerHUDComp.hpp
** File description:
** Created by Achille Bourgault
*/

#ifndef PlayerHUDComp_HPP
#define PlayerHUDComp_HPP

#include <GUI/TextComp.hpp>
#include <GUI/SpriteComp.hpp>
#include "SFML/Graphics.hpp"
#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"
#include "ECS/Manager.hpp"
#include "TransformComp.hpp"
#include "Components/GUI/SubPanelComp.hpp"

class PlayerHUDComp : public Component {
public:
    explicit PlayerHUDComp();
    void draw() override;
    void init() override;
    void update(double t, double dt, Manager::PlayerInputs inputs) override;

private:
    SubPanelComp *hud;
    TextComp *scoreTextLabel;
    TextComp *scoreTextValue;
    TextComp *healthTextValue;
    TransformComp *transform;
    SpriteComp *playerIcon;
};

#endif //PlayerHUDComp_HPP
