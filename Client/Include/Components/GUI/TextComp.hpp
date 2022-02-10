/*
** EPITECH PROJECT, 2024
** TextComp.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef TEXTCOMP_HPP
#define TEXTCOMP_HPP
#include "SFML/Graphics.hpp"
#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"
#include "ECS/Manager.hpp"
#include "TransformComp.hpp"

class TextComp : public Component {
public:
    explicit TextComp(std::string str, int size = 50, sf::Color color = sf::Color::White);;
    void draw() override;
    void init() override;
    void update(double t, double dt, Manager::PlayerInputs inputs) override;
    void centerHorizontally();

    sf::Text text;
    sf::Font font;
    sf::Color color;
private:
    TransformComp *transform;
};

#endif //TEXTCOMP_HPP
