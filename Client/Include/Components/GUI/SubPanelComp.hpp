/*
** EPITECH PROJECT, 2024
** SubPanelComp.hpp
** File description:
** Created by Achille Bourgault
*/

#ifndef SubPanelComp_HPP
#define SubPanelComp_HPP
#include "SFML/Graphics.hpp"
#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"
#include "ECS/Manager.hpp"
#include "TransformComp.hpp"

class SubPanelComp : public Component {
public:
    explicit SubPanelComp(int width, int height, sf::Color color = sf::Color::White);
    void draw() override;
    void init() override;
    void update(double t, double dt, Manager::PlayerInputs inputs) override;

    sf::RectangleShape shape;
    private:
    TransformComp *transform;
};

#endif //SubPanelComp_HPP
